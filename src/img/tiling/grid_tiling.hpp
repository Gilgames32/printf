#pragma once
#include "tiling.hpp"

class GridTiling : public Tiling {
    // calculates the wasted area on the sides of the document
    size_t calc_waste(size_t document_width, size_t tile_width, size_t tile_height, size_t amount);

  public:
    cv::Mat generate(const DocumentPreset& preset, std::vector<ImageSource> images) override;
};