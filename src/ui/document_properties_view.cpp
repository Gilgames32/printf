#include "document_properties_view.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

// TODO: remove constants
DocumentPropertiesView::DocumentPropertiesView()
    : m_resolution(300), m_roll_width(609.6), m_margin(5), m_correct_quantity(false), m_guides(true), m_gutter(2) {}

void DocumentPropertiesView::load_from_preset(const std::string& preset_path) {
    std::cout << "Loading preset from: " << preset_path << std::endl;

    if (!std::filesystem::exists(preset_path)) {
        throw std::invalid_argument("Preset file does not exist: " + preset_path);
    }

    json j;
    std::ifstream f(preset_path);
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open preset file: " + preset_path);
    }
    j = json::parse(f);
    f.close();

    if (j.contains("resolution_ppi")) {
        m_resolution = j["resolution_ppi"].get<double>();
        emit resolutionChanged();
    }
    if (j.contains("roll_width_mm")) {
        m_roll_width = j["roll_width_mm"].get<double>();
        emit rollWidthChanged();
    }
    if (j.contains("margin_mm")) {
        m_margin = j["margin_mm"].get<double>();
        emit marginChanged();
    }
    if (j.contains("gutter_mm")) {
        m_gutter = j["gutter_mm"].get<double>();
        emit gutterChanged();
    }
    if (j.contains("correct_quantity")) {
        m_correct_quantity = j["correct_quantity"].get<bool>();
        emit correctQuantityChanged();
    }
    if (j.contains("guide")) {
        m_guides = j["guide"].get<bool>();
        emit guidesChanged();
    }
}

void DocumentPropertiesView::setPreset(const QString& presetPath) { load_from_preset(presetPath.toStdString()); }

DocumentPreset DocumentPropertiesView::getDocumentProperties() const {
    return DocumentPreset(m_resolution, m_roll_width, m_margin, m_gutter, m_correct_quantity, m_guides,
                          1000,  // TODO: remove constant
                          18000  // TODO: remove constant
    );
}
