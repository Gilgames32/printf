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
    std::string name;
    
    double ppi;
    double roll_width_mm;
    double margin_mm;
    double gutter_mm;
    
    bool correct_quantity;
    bool guide;

    double min_height_mm;
    double max_height_mm;

  public:
    DocumentPreset(std::string path);

    size_t get_document_width_px() const;

    size_t get_max_height_px() const;

    size_t get_min_height_px() const;
};
