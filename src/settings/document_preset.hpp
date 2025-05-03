#pragma once
#include <cstddef>
#include <string>

/*
TODO:
ppi
roll witdth - margin * 2 = document width
min max height
*/

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
        double roll_width_mm = 600,
        double margin_mm = 5,
        double gutter_mm = 5,
        bool correct_quantity = false,
        bool guide = false,
        double min_height_mm = 1000,
        double max_height_mm = 18000
    );
  
    DocumentPreset(std::string path);

    size_t get_document_width_px() const;

    size_t get_max_height_px() const;

    size_t get_min_height_px() const;

    size_t get_gutter_px() const;

    bool get_guide() const;

    bool get_correct_quantity() const;
};
