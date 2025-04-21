#include "mask_filter_view.hpp"

#include <filesystem>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <stdexcept>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

MaskFilterView::MaskFilterView(): m_is_enabled(false) {}

QString MaskFilterView::get_file_name() const {
    return QString::fromStdString(std::filesystem::path(m_file_path).filename().string());
}

QString MaskFilterView::get_file_path() const { return QString::fromStdString(m_file_path); }

QString MaskFilterView::get_absolute_file_path() const {
    std::filesystem::path path(m_file_path);
    if (std::filesystem::exists(path) && path.is_relative()) {
        return QString::fromStdString(std::filesystem::absolute(path).string());
    }
    return QString::fromStdString(m_file_path);
}

float MaskFilterView::get_image_aspect_ratio() const { return float(m_image.cols) / float(m_image.rows); }

cv::Mat MaskFilterView::get_image() const { return m_image; }

void MaskFilterView::load_from_preset(const std::string& preset_path) {
    std::cout << "Loading preset from: " << preset_path << std::endl;

    if (!std::filesystem::exists(preset_path)) {
        throw std::invalid_argument("Preset file does not exist: " + preset_path);
    }

    json json_data;
    std::ifstream file(preset_path);
    json_data = json::parse(file);
    file.close();

    // TODO: handle errors
    m_file_path = json_data["path"].get<std::string>();
    // TODO: load m_image
}

void MaskFilterView::setPreset(const QString& presetPath) {
    load_from_preset(presetPath.toStdString());
    // TODO: update signals
    emit filePathChanged();
    emit nameChanged();
}