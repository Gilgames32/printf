#pragma once
#include <opencv2/imgproc.hpp>

#include "filter.hpp"

class PaddingFilter : public Filter {
  private:
    size_t padding;
    bool guide;

  public:
    PaddingFilter(size_t padding, bool guide = false);

    cv::Mat apply(const cv::Mat &image) const override;
};