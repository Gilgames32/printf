#include "generator_view.hpp"

#include <iostream>

GeneratorView::GeneratorView() {}

void GeneratorView::generate(const DocumentPreset& properties, QList<ImageSource*> sources) {
    qDebug() << "Generating with the following properties:";
    qDebug() << "Resolution:" << properties.get_document_width_px();
    qDebug() << "Roll Width:" << properties.get_document_width_px();

    qDebug() << "Count of sources:" << sources.size();
}

