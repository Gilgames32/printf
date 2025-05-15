#pragma once
#include <opencv2/imgproc.hpp>

#include "ifilter.hpp"

class PaddingFilter : public IFilter {
  private:
    size_t padding;
    bool guide;
    int bleed; // -1 for full lines
    int line_thickness;
    cv::Scalar line_color;
    cv::Scalar bg_color = cv::Scalar(255, 255, 255);

  public:
    // TODO config
    PaddingFilter(size_t padding, bool guide = false, int bleed = 0,
                  int line_thickness = 1, cv::Scalar line_color = cv::Scalar(0, 0, 0));

    cv::Mat apply(const cv::Mat &image) const override;
};