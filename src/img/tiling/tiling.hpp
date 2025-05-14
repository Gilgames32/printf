#pragma once
#include "document_preset.hpp"
#include "image_source.hpp"
#include <memory>

class Tiling {
  public:
    virtual cv::Mat generate(const DocumentPreset &preset, std::vector<std::shared_ptr<ImageSource>> images) = 0;
};

