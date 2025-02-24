#pragma once

#include <opencv2/opencv.hpp>

// TODO
class CachedImage {
  private:
    cv::Mat image;
    bool isDirty;

  public:
    CachedImage();
    ~CachedImage();
};
