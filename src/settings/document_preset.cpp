#include "document_preset.hpp"

#include <stdexcept>

DocumentPreset::DocumentPreset(double ppi, double roll_width_mm, double margin_mm, double gutter_mm, bool correct_quantity,
                               bool guide, int line_width, double min_height_mm, double max_height_mm)
    : ppi(ppi),
      roll_width_mm(roll_width_mm),
      margin_mm(margin_mm),
      gutter_mm(gutter_mm),
      correct_quantity(correct_quantity),
      guide(guide),
      line_width(line_width),
      min_height_mm(min_height_mm),
      max_height_mm(max_height_mm) {
    if (ppi <= 0) throw std::invalid_argument("Invalid ppi");
    if (roll_width_mm <= 0) throw std::invalid_argument("Invalid roll width");
    if (margin_mm < 0) throw std::invalid_argument("Invalid margin");
    if (gutter_mm < 0) throw std::invalid_argument("Invalid gutter");
    if (line_width < 0) throw std::invalid_argument("Invalid line width");
    if (min_height_mm <= 0) throw std::invalid_argument("Invalid minimum height");
    if (max_height_mm <= 0 || min_height_mm > max_height_mm) throw std::invalid_argument("Invalid maximum height");
}
