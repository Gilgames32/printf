#pragma once

#include "settings/document_presets.hpp"
#include "source.hpp"

namespace tiling {

    void recursive_packing(std::vector<Tile> rects, cv::Point current_point, size_t remainging_width, size_t current_height);

    std::pair<int, std::vector<Tile>> tile(std::vector<Tile> rects, const DocumentPreset& preset);

    cv::Mat generate(std::vector<const ImgSource&> images, const DocumentPreset& preset);
};  // namespace tiling
