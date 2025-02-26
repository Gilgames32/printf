#include "size.hpp"

SizeFilter::SizeFilter(int width, int height) : width(width), height(height) {}

cv::Mat SizeFilter::apply(const cv::Mat &image) const { return SizeFilter::resize(image, width, height); }

cv::Mat SizeFilter::resize(const cv::Mat &image, int width, int height, int interDown, int interUp) {
    if (width == image.cols && height == image.rows) {
        return image;
    }

    bool downScaling = width < image.cols || height < image.rows;

    cv::Mat resized;
    cv::resize(image, resized, cv::Size(width, height), 0, 0, downScaling ? interDown : interUp);

    return resized;
}
