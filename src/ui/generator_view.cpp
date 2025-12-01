#include "generator_view.hpp"

#include <QtConcurrent/QtConcurrent>
#include <exiv2/exiv2.hpp>
#include <iostream>

#include "grid_tiling.hpp"
#include "strip_tiling.hpp"
#include "preview_provider.hpp"
#include "pnghelper.hpp"
#include "error_signal.hpp"
#include "convert.hpp"

GeneratorView::GeneratorView() {}

void GeneratorView::generate(const DocumentPreset& properties, const QList<std::shared_ptr<ImageSource>>& sources) {
    std::vector<std::shared_ptr<ImageSource>> sources_vector(sources.constBegin(), sources.constEnd());
    
    if (sources_vector.empty()) {
        throw std::invalid_argument("No image sources provided");
    }
    
    Tiling* tiling;
    if (sources_vector.size() == 1) {
        tiling = new GridTiling();
    } else {
        tiling = new StripTiling();
    }
    cv::Mat result = tiling->generate(properties, sources_vector);
    delete tiling;

    if (result.empty()) {
        throw std::runtime_error("Failed to generate image");
    }

    QImage image(result.data, result.cols, result.rows, result.step, QImage::Format_BGR888);
    PreviewProvider::instance()->setImage(image.copy());

}

QFuture<void> GeneratorView::asyncGenerate(const DocumentPreset& properties, const QList<std::shared_ptr<ImageSource>>& sources) {
    return QtConcurrent::run([=, this]() {
        ErrorSignal::iinfo("Generating image...");
        try {
            generate(properties, sources);
            const QImage& img = PreviewProvider::instance()->getImage();
            const auto width = img.width();
            const auto height = img.height();
            const auto ppi = properties.get_ppi();
                
            // TODO: handle properly
            if (height > properties.get_max_height_px()) 
                ErrorSignal::ierror("Generated image exceeds maximum height");
            else if (height < properties.get_min_height_px()) 
                ErrorSignal::ierror("Generated image is below minimum height");
            else 
                ErrorSignal::iinfo(QString("%1 x %2 px - %3 x %4 mm").arg(width).arg(height).arg(convert::pixel_to_mm(width, ppi)).arg(convert::pixel_to_mm(height, ppi)));
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            PreviewProvider::instance()->setImage(QImage());
            ErrorSignal::ierror(e.what());
        }
        emit generationCompleted();
    });
}

void GeneratorView::save(const QString& path, const DocumentPreset& properties) {
    const QImage& image = PreviewProvider::instance()->getImage().convertToFormat(QImage::Format_RGB888);
    if (image.isNull()) {
        throw std::runtime_error("Image is null");
    }

    auto out_path = path.toStdString();
    if (out_path.rfind("file://", 0) == 0) {
        out_path = out_path.substr(7);
    }
    
    // TODO: save as jpeg
    PNGHelper::save_png(out_path, image, properties.get_ppi());
    PNGHelper::add_exif_data(out_path, properties);
}

QFuture<void> GeneratorView::asyncSave(const QString& path, const DocumentPreset& properties) {
    return QtConcurrent::run([=, this]() {
        ErrorSignal::iinfo("Saving image...");
        try {
            save(path, properties);
            ErrorSignal::iinfo("Saved image to " + path);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            PreviewProvider::instance()->setImage(QImage());
            ErrorSignal::ierror(e.what());
        }
        emit saveCompleted();
    });
}
