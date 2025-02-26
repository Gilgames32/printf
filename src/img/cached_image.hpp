#pragma once

#include <opencv2/opencv.hpp>
#include "interfaces/icachable.hpp"
#include "interfaces/icache.hpp"

class CachedImage : ICache {
  private:
    const ICachableImage& source;
    cv::Mat cache;
    bool isDirty;

  public:
    CachedImage(const ICachableImage& source);
    cv::Mat get_img();

    void set_dirty() override;
};
