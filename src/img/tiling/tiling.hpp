#pragma once
#include "document_preset.hpp"
#include "image_source.hpp"
#include <memory>

class Tiling {
  public:
    virtual cv::Mat generate(const DocumentPreset &preset, const std::vector<ImageSource*>& images) = 0;
    virtual ~Tiling() = default;
};

