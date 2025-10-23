#include "rotate.hpp"

RotateFilter::RotateFilter(bool rotated, cv::RotateFlags rotation_dir) : rotated(rotated), rotation_dir(rotation_dir) {}

bool RotateFilter::get_rotated() const { return rotated; }

void RotateFilter::set_rotated(bool rotated) { this->rotated = rotated; }

cv::Mat RotateFilter::apply(const cv::Mat& image) const {
    return rotated ? RotateFilter::rotate(image, rotation_dir) : image;
}

cv::Mat RotateFilter::rotate(const cv::Mat &image, cv::RotateFlags rotation_dir) {
    cv::Mat rotated;
    cv::rotate(image, rotated, rotation_dir);
    return rotated;
}
