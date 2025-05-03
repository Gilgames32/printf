#include "generator_view.hpp"

#include <iostream>

#include "grid_tiling.hpp"
#include "preview_provider.hpp"

GeneratorView::GeneratorView() {}

void GeneratorView::generate(const DocumentPreset& properties, QList<ImageSource*> sources) {
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
