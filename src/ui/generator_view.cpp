#include "generator_view.hpp"

#include <QtConcurrent/QtConcurrent>
#include <exiv2/exiv2.hpp>
#include <iostream>

#include "grid_tiling.hpp"
#include "preview_provider.hpp"
#include "pnghelper.hpp"

GeneratorView::GeneratorView() {}

void GeneratorView::generate(const DocumentPreset& properties, const QList<ImageSource*>& sources) {
    // TODO cleanup
    qDebug() << "Generating...";
    qDebug() << "Roll Width:" << properties.get_document_width_px();
    qDebug() << "Count of sources:" << sources.size();

    std::vector<ImageSource*> sources_vector(sources.constBegin(), sources.constEnd());
    GridTiling tiling = GridTiling();  // TODO: other tiling methods
    cv::Mat result = tiling.generate(properties, sources_vector);

    if (result.empty()) {
        qDebug() << "Failed to generate image.";
        for (auto img : sources) {
            delete img;
        }
        return;
    }

    // Convert cv::Mat to QImage
    QImage image(result.data, result.cols, result.rows, result.step, QImage::Format_RGB888);
    PreviewProvider::instance()->setImage(image.rgbSwapped());
    for (auto img : sources) {
        delete img;
    }

    qDebug() << "Image generation completed and set to provider.";
}

QFuture<void> GeneratorView::asyncGenerate(const DocumentPreset& properties, const QList<ImageSource*>& sources) {
    return QtConcurrent::run([=]() {
        try {
            generate(properties, sources);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            qDebug() << "Exception occurred during generation:" << e.what();
        }

        qDebug() << "Async generation completed.";
        emit generationCompleted();
    });
}

void GeneratorView::save(const QString& path, const DocumentPreset& properties) {
    auto out_path = path.toStdString();
    if (out_path.rfind("file://", 0) == 0) {
        out_path = out_path.substr(7);
    }

    qDebug() << "Saving to" << out_path.c_str();
    QImage image = PreviewProvider::instance()->getImage();



    try {
        // TODO: save as jpeg
        PNGHelper::save_png(out_path, image, properties.get_ppi());
        PNGHelper::add_exif_data(out_path, properties);
        
        qDebug() << "Image saved successfully.";
    } catch (const std::exception& e) {
        qDebug() << "Error saving image:" << e.what();
    }
}

QFuture<void> GeneratorView::asyncSave(const QString& path, const DocumentPreset& properties) {
    return QtConcurrent::run([=]() {
        try {
            save(path, properties);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            qDebug() << "Exception occurred during saving:" << e.what();
        }

        qDebug() << "Async saving completed.";
        emit saveCompleted();
    });
}
