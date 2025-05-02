#include "generator_view.hpp"

#include <iostream>
#include "grid_tiling.hpp"

GeneratorView::GeneratorView() {}

void GeneratorView::generate(const DocumentPreset& properties, QList<ImageSource*> sources) {
    qDebug() << "Generating...";
    qDebug() << "Roll Width:" << properties.get_document_width_px();
    qDebug() << "Count of sources:" << sources.size();

    std::vector<ImageSource*> sources_vector(sources.constBegin(), sources.constEnd());
    GridTiling tiling = GridTiling(); // TODO: other tiling methods
    cv::Mat result = tiling.generate(properties, sources_vector);
    
    
    if (result.empty()) {
        qDebug() << "Failed to generate image.";
        return;
    }
    std::string output_path = "output.png"; // TODO: get from settings
    cv::imwrite(output_path, result);
    qDebug() << "Image saved to:" << QString::fromStdString(output_path);
    qDebug() << "Generation completed.";
}

