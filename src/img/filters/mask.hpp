#pragma once
#include <opencv2/imgproc.hpp>

#include "filter.hpp"

class MaskFilter : public Filter {
  private:
    cv::Mat mask;
    bool invert = false;

  public:
    MaskFilter(const cv::Mat &mask);

    cv::Mat apply(const cv::Mat &image) override;

    void setInvert(bool invert);
};
