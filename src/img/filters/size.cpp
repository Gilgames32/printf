#include "size.hpp"

SizeFilter::SizeFilter(int width, int height) : width(width), height(height), isUniform(true) {}

cv::Mat &SizeFilter::apply(const cv::Mat &image)
{
    cv::Mat resized;

    bool downScaling = width < image.cols || height < image.rows;

    cv::resize(image, resized, cv::Size(width, height), 0, 0, downScaling ? downScalingInterpolation : upScalingInterpolation);
    return resized;
}
