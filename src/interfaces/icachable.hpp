#pragma once

#include <opencv2/opencv.hpp>

class ICachableImage {
  public:
    virtual cv::Mat get_cachable() const = 0;
};