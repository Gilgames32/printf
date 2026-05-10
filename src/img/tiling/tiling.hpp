#pragma once
#include <memory>

#include "document_preset.hpp"
#include "image_source.hpp"

class Tiling {
  public:
    virtual cv::Mat generate(const DocumentPreset& preset, const std::vector<ImageSource*>& images) = 0;
    virtual ~Tiling() = default;
};
