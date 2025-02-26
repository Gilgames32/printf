#include "rotate.hpp"

cv::Mat RotateFilter::apply(const cv::Mat &image) const { return RotateFilter::rotate(image, default_rotation_dir); }

cv::Mat RotateFilter::rotate(const cv::Mat &image, cv::RotateFlags rotation_dir) {
    cv::Mat rotated;
    cv::rotate(image, rotated, rotation_dir);
    return rotated;
}
