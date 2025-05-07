#pragma once
#include <opencv2/imgproc.hpp>

#include "ifilter.hpp"

class MaskFilter : public IFilter {
  private:
    cv::Mat mask;
    bool invert = false;

  public:
    MaskFilter(const cv::Mat &mask);

    cv::Mat apply(const cv::Mat &image) const override;

    void setInvert(bool invert);
};
