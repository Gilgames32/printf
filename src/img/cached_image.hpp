#pragma once

#include <opencv2/opencv.hpp>
#include "icachable.hpp"
#include "icache.hpp"

class CachedImage : ICache {
  private:
    const ICachableImage& source;
    cv::Mat cache;
    bool isDirty;

    
    public:
    CachedImage(const ICachableImage& source);
    
    void regenerate();
    
    cv::Mat get_img();
    
    int get_width();

    int get_height();

    void set_dirty() override;
};
