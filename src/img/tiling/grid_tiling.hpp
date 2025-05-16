#pragma once
#include "tiling.hpp"

class GridTiling : public Tiling {
    // calculates the wasted area on the sides of the document
    int calc_waste(int document_width, int tile_width, int tile_height, int amount);

  public:
    cv::Mat generate(const DocumentPreset& preset, std::vector<std::shared_ptr<ImageSource>> images) override;
};