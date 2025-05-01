#include "document_properties_view.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// TODO: remove constants
DocumentPropertiesView::DocumentPropertiesView(): m_resolution(300), m_roll_width(600), m_margin(5), m_correct_quantity(false) {}

void DocumentPropertiesView::load_from_preset(const std::string& preset_path) {
    std::cout << "Loading preset from: " << preset_path << std::endl;

    if (!std::filesystem::exists(preset_path)) {
        throw std::invalid_argument("Preset file does not exist: " + preset_path);
    }

    json json_data;
    std::ifstream file(preset_path);
    json_data = json::parse(file);
    file.close();

    // TODO: handle errors
    m_resolution = json_data["resolution_ppi"].get<double>();
    m_roll_width = json_data["roll_width_mm"].get<double>();
    m_margin = json_data["margin_mm"].get<double>();
}

void DocumentPropertiesView::setPreset(const QString& presetPath) {
    load_from_preset(presetPath.toStdString());
    // TODO: update signals
    emit resolutionChanged();
    emit rollWidthChanged();
    emit marginChanged();
}