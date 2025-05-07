#include "mask.hpp"

#include "size.hpp"

MaskFilter::MaskFilter(const cv::Mat &mask) : mask(mask) {}

cv::Mat MaskFilter::apply(const cv::Mat &image) const {
    // convert mask
    auto fitMask = SizeFilter::resize(mask, image.cols, image.rows);
    if (invert) {
        cv::bitwise_not(fitMask, fitMask);
    }
    fitMask.convertTo(fitMask, CV_32FC3, 1.0 / 255.0);

    // background
    cv::Mat white(image.size(), CV_32FC3, cv::Scalar(1.0, 1.0, 1.0));
    
    // convert image
    cv::Mat imagef;
    image.convertTo(imagef, CV_32FC3, 1.0 / 255.0);

    cv::Mat blended;
    cv::multiply(fitMask, imagef, imagef);
    cv::multiply(cv::Scalar(1.0, 1.0, 1.0) - fitMask, white, white);
    cv::add(imagef, white, blended);
    blended.convertTo(blended, CV_8UC3, 255.0);
    
    return blended;
}

void MaskFilter::setInvert(bool invert) { this->invert = invert; }
