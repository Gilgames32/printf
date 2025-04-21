#pragma once

#include <opencv2/opencv.hpp>
#include "icachable.hpp"
#include "icache.hpp"

class CachedImage : ICache {
  private:
    const ICachableImage& source;
    cv::Mat cache;
    bool isDirty;

    void regenerate();

  public:
    CachedImage(const ICachableImage& source);
    
    cv::Mat get_img();

    size_t get_width();

    size_t get_height();

    void set_dirty() override;
};
