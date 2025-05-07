#pragma once
#include <cstddef>
#include <string>

class DocumentPreset {
  private:
    double ppi;
    double roll_width_mm;
    double margin_mm;
    double gutter_mm;
    
    bool correct_quantity;
    bool guide;

    double min_height_mm;
    double max_height_mm;

  public:
    DocumentPreset(
        // FIXME
        double ppi = 300,
        double roll_width_mm = 609.6,
        double margin_mm = 5,
        double gutter_mm = 2,
        bool correct_quantity = false,
        bool guide = true,
        double min_height_mm = 101.6,
        double max_height_mm = 18000
    );

    double get_ppi() const;

    size_t get_document_width_px() const;

    size_t get_max_height_px() const;

    size_t get_min_height_px() const;

    size_t get_gutter_px() const;

    bool get_guide() const;

    bool get_correct_quantity() const;
};
