#include "generator_view.hpp"

#include <QtConcurrent/QtConcurrent>
#include <exiv2/exiv2.hpp>
#include <iostream>

#include "grid_tiling.hpp"
#include "preview_provider.hpp"
#include "pnghelper.hpp"

GeneratorView::GeneratorView() {}

void GeneratorView::generate(const DocumentPreset& properties, const QList<std::shared_ptr<ImageSource>>& sources) {
    std::vector<std::shared_ptr<ImageSource>> sources_vector(sources.constBegin(), sources.constEnd());
    
    GridTiling tiling = GridTiling();  // TODO: other tiling methods
    cv::Mat result = tiling.generate(properties, sources_vector);
    if (result.empty()) {
        throw std::runtime_error("Failed to generate image");
    }

    QImage image(result.data, result.cols, result.rows, result.step, QImage::Format_BGR888);
    PreviewProvider::instance()->setImage(image.copy());
}

QFuture<void> GeneratorView::asyncGenerate(const DocumentPreset& properties, const QList<std::shared_ptr<ImageSource>>& sources) {
    return QtConcurrent::run([=]() {
        try {
            generate(properties, sources);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            qDebug() << "Exception occurred during generation:" << e.what();
        }
        emit generationCompleted();
    });
}

void GeneratorView::save(const QString& path, const DocumentPreset& properties) {
    const QImage& image = PreviewProvider::instance()->getImage();
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
    return QtConcurrent::run([=]() {
        try {
            save(path, properties);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            qDebug() << "Exception occurred during saving:" << e.what();
        }
        emit saveCompleted();
    });
}
