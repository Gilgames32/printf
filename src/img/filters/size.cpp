#include "size.hpp"

SizeFilter::SizeFilter(int width, int height) : width(width), height(height) {}

void SizeFilter::set_size(int width, int height) {
    this->width = width;
    this->height = height;
}

cv::Mat SizeFilter::apply(const cv::Mat &image) const { return SizeFilter::resize(image, width, height); }

cv::Mat SizeFilter::resize(const cv::Mat &image, int width, int height, int interDown, int interUp) {
    if (width == image.cols && height == image.rows) {
        return image;
    }
    if (width <= 0 || height <= 0) {
        return cv::Mat();
    }

    bool downScaling = width < image.cols || height < image.rows;

    cv::Mat resized;
    cv::resize(image, resized, cv::Size(width, height), 0, 0, downScaling ? interDown : interUp);

    return resized;
}

cv::Mat SizeFilter::resize_to_width(const cv::Mat &image, int width, int interDown, int interUp) {
    return SizeFilter::resize(image, width, image.rows * width / image.cols, interDown, interUp);
}
