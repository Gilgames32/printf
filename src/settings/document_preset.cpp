#include "document_preset.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

#include "convert.hpp"

using json = nlohmann::json;

DocumentPreset::DocumentPreset(double ppi, double roll_width_mm, double margin_mm, double gutter_mm, bool correct_quantity,
                               bool guide, double min_height_mm, double max_height_mm)
    : ppi(ppi),
      roll_width_mm(roll_width_mm),
      margin_mm(margin_mm),
      gutter_mm(gutter_mm),
      correct_quantity(correct_quantity),
      guide(guide),
      min_height_mm(min_height_mm),
      max_height_mm(max_height_mm) {}

DocumentPreset::DocumentPreset(std::string path) {
    std::ifstream f(path);
    json data = json::parse(f);
    f.close();

    ppi = data["resolution_ppi"];
    roll_width_mm = data["roll_width_mm"];
    margin_mm = data["margin_mm"];
    gutter_mm = data["gutter_mm"];

    guide = data["guide"];
    correct_quantity = data["correct_quantity"];

    // FIXME
    max_height_mm = 18000;
    min_height_mm = 1000;
}

size_t DocumentPreset::get_document_width_px() const { return convert::mm_to_pixels(roll_width_mm - margin_mm * 2, ppi); }

size_t DocumentPreset::get_max_height_px() const { return convert::mm_to_pixels(max_height_mm, ppi); }

size_t DocumentPreset::get_min_height_px() const { return convert::mm_to_pixels(min_height_mm, ppi); }

size_t DocumentPreset::get_gutter_px() const { return convert::mm_to_pixels(gutter_mm, ppi); }

bool DocumentPreset::get_guide() const { return guide; }

bool DocumentPreset::get_correct_quantity() const { return correct_quantity; }
