#include "pdf_source_view.hpp"
#include <poppler-qt6.h>

PDFSourceView::PDFSourceView() : ImageSourceView() {}

void PDFSourceView::load_image() {

    auto doc = Poppler::Document::load(QString::fromStdString(m_file_path));
    if (!doc) {
        throw std::runtime_error("Failed to load pdf: " + m_file_path);
    }
    
    auto page = doc->page(0);
    if (!page) {
        throw std::runtime_error("Failed to the first page of the pdf: " + m_file_path);
    }
    // https://poppler.freedesktop.org/api/qt6/classPoppler_1_1Document.html#a8420ce678235ee6214fbd91f5ae2f4e9
    doc->setRenderHint(Poppler::Document::Antialiasing);
    doc->setRenderHint(Poppler::Document::TextAntialiasing);
    doc->setRenderHint(Poppler::Document::ThinLineSolid);

    QImage img = page->renderToImage(300, 300); // TODO follow document size
    if (img.isNull()) {
        throw std::runtime_error("Failed to render the pdf: " + m_file_path);
    }

    m_image = cv::Mat(img.height(), img.width(), CV_8UC4, img.bits(), img.bytesPerLine()).clone();
}