#pragma once
#include "document_presets.hpp"
#include "image_source.hpp"

class Tiling {
  public:
    virtual cv::Mat generate(const DocumentPreset &preset, std::vector<ImageSource> images) = 0;
};

