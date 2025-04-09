#include "image_source_view.hpp"

#include <filesystem>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <stdexcept>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// TODO: dont hardcode the initial amount
ImageSourceView::ImageSourceView(const std::string& path) : m_file_path(path), m_amount(20) {
    if (m_file_path.rfind("file://", 0) == 0) {
        m_file_path = m_file_path.substr(7);
    }

    if (!std::filesystem::exists(m_file_path)) {
        throw std::invalid_argument("File does not exist: " + m_file_path);
    }

    m_image = cv::imread(m_file_path);
    if (m_image.empty()) {
        throw std::runtime_error("Failed to load image: " + m_file_path);
    }

    m_width = m_image.cols;
    m_height = m_image.rows;
}

QString ImageSourceView::get_file_name() const {
    return QString::fromStdString(std::filesystem::path(m_file_path).filename().string());
}

QString ImageSourceView::get_file_path() const { return QString::fromStdString(m_file_path); }

QSize ImageSourceView::get_image_resolution() const { return QSize(m_image.cols, m_image.rows); }

float ImageSourceView::get_image_aspect_ratio() const { return float(m_image.cols) / float(m_image.rows); }

cv::Mat ImageSourceView::get_image() const { return m_image; }

void ImageSourceView::load_from_preset(const std::string& preset_path) {
    std::cout << "Loading preset from: " << preset_path << std::endl;

    if (!std::filesystem::exists(preset_path)) {
        throw std::invalid_argument("Preset file does not exist: " + preset_path);
    }

    json json_data;
    std::ifstream file(preset_path);
    json_data = json::parse(file);
    file.close();

    m_width = json_data["width"];
    m_height = json_data["height"];
}

Q_INVOKABLE void ImageSourceView::setPreset(const QString& presetPath) {
    load_from_preset(presetPath.toStdString());
    // TODO: update signals
    widthChanged();
    heightChanged();
}