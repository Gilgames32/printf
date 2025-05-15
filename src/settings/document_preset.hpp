#pragma once
#include <cstddef>
#include <string>
#include "convert.hpp"

class DocumentPreset {
  private:
    double ppi;
    double roll_width_mm;
    double margin_mm;
    double gutter_mm;

    bool correct_quantity;
    bool guide;
    int line_width;

    double min_height_mm;
    double max_height_mm;

  public:
    DocumentPreset(
        // FIXME
        double ppi = 300, double roll_width_mm = 609.6, double margin_mm = 0, double gutter_mm = 2,
        bool correct_quantity = false, bool guide = true, int line_width = 1, double min_height_mm = 101.6,
        double max_height_mm = 18000);

    double get_ppi() const { return ppi; }

    double get_ppm() const { return convert::ppi_to_ppm(ppi); }

    size_t get_document_width_px() const { return convert::mm_to_pixel(roll_width_mm - margin_mm * 2, ppi); }

    size_t get_max_height_px() const { return convert::mm_to_pixel(max_height_mm, ppi); }

    size_t get_min_height_px() const { return convert::mm_to_pixel(min_height_mm, ppi); }

    size_t get_gutter_px() const { return convert::mm_to_pixel(gutter_mm, ppi); }

    size_t get_padding_px() const { return convert::mm_to_pixel(gutter_mm / 2.0, ppi); }

    bool get_guide() const { return guide; }

    bool get_correct_quantity() const { return correct_quantity; }

    bool get_line_width() const { return guide ? line_width : 0; };
};
