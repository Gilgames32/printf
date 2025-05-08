#pragma once
#include <opencv2/imgproc.hpp>

#include "ifilter.hpp"

class RotateFilter : public IFilter {
  private:
    static const cv::RotateFlags default_rotation_dir = cv::ROTATE_90_CLOCKWISE;

  public:
    cv::Mat apply(const cv::Mat &image) const override;
    static cv::Mat rotate(const cv::Mat &image, cv::RotateFlags rotation_dir);
};
