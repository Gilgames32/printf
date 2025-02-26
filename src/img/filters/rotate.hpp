#pragma once
#include <opencv2/imgproc.hpp>

#include "filter.hpp"

class RotateFilter : public Filter {
  private:
    static const cv::RotateFlags default_rotation_dir = cv::ROTATE_90_CLOCKWISE;

  public:
    cv::Mat apply(const cv::Mat &image) const override;
    static cv::Mat rotate(const cv::Mat &image, cv::RotateFlags rotation_dir);
};
