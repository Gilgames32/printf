#pragma once
#include <opencv2/imgproc.hpp>

#include "ifilter.hpp"

class PaddingFilter : public IFilter {
  private:
    size_t padding;
    bool guide;

  public:
    PaddingFilter(size_t padding, bool guide = false);

    cv::Mat apply(const cv::Mat &image) const override;
};