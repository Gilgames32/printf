#include "mask.hpp"

#include "size.hpp"

MaskFilter::MaskFilter(const cv::Mat &mask) : mask(mask) {}

cv::Mat MaskFilter::apply(const cv::Mat &image) const {
    auto fitMask = SizeFilter::resize(mask, image.cols, image.rows);

    if (invert) {
        cv::bitwise_not(fitMask, fitMask);
    }
    cv::normalize(fitMask, fitMask, 0., 1., cv::NORM_MINMAX, CV_32F);

    cv::Mat result;
    image.convertTo(result, CV_32F);

    cv::multiply(result, fitMask, result);

    result.convertTo(result, CV_8U);
    return result;
}

void MaskFilter::setInvert(bool invert) { this->invert = invert; }
