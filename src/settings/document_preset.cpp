#include "document_preset.hpp"

#include <fstream>
#include <stdexcept>

#include "convert.hpp"

DocumentPreset::DocumentPreset(double ppi, double roll_width_mm, double margin_mm, double gutter_mm, bool correct_quantity,
                               bool guide, double min_height_mm, double max_height_mm)
    : ppi(ppi),
      roll_width_mm(roll_width_mm),
      margin_mm(margin_mm),
      gutter_mm(gutter_mm),
      correct_quantity(correct_quantity),
      guide(guide),
      min_height_mm(min_height_mm),
      max_height_mm(max_height_mm) {
    if (ppi <= 0) throw std::invalid_argument("Invalid ppi");
    if (roll_width_mm <= 0) throw std::invalid_argument("Invalid roll width");
    if (margin_mm < 0) throw std::invalid_argument("Invalid margin");
    if (gutter_mm < 0) throw std::invalid_argument("Invalid gutter");
    if (min_height_mm <= 0) throw std::invalid_argument("Invalid minimum height");
    if (max_height_mm <= 0 || min_height_mm > max_height_mm) throw std::invalid_argument("Invalid maximum height");
}

double DocumentPreset::get_ppi() const { return ppi; }

double DocumentPreset::get_ppm() const { return convert::ppi_to_dpi(ppi); }

size_t DocumentPreset::get_document_width_px() const { return convert::mm_to_pixel(roll_width_mm - margin_mm * 2, ppi); }

size_t DocumentPreset::get_max_height_px() const { return convert::mm_to_pixel(max_height_mm, ppi); }

size_t DocumentPreset::get_min_height_px() const { return convert::mm_to_pixel(min_height_mm, ppi); }

size_t DocumentPreset::get_gutter_px() const { return convert::mm_to_pixel(gutter_mm, ppi); }

size_t DocumentPreset::get_padding_px() const { return convert::mm_to_pixel(gutter_mm / 2.0, ppi); }

bool DocumentPreset::get_guide() const { return guide; }

bool DocumentPreset::get_correct_quantity() const { return correct_quantity; }
