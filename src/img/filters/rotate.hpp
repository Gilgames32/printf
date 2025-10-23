#pragma once
#include <opencv2/imgproc.hpp>

#include "ifilter.hpp"

class RotateFilter : public IFilter {
  private:
    bool rotated;
    cv::RotateFlags rotation_dir;

  public:
    RotateFilter(bool is_rotated = false, cv::RotateFlags rotation_dir = cv::ROTATE_90_CLOCKWISE);
    bool get_rotated() const;
    void set_rotated(bool rotated);

    cv::Mat apply(const cv::Mat &image) const override;
    static cv::Mat rotate(const cv::Mat &image, cv::RotateFlags rotation_dir);
};
