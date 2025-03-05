#include "padding.hpp"

PaddingFilter::PaddingFilter(size_t padding, bool guide): padding(padding), guide(guide) {}

cv::Mat PaddingFilter::apply(const cv::Mat &image) const {
    cv::Mat padded;
    cv::copyMakeBorder(image, padded, padding, padding, padding, padding, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));

    if (guide) {
        // TODO: make this configurable
        int thickness = 1;
        cv::Scalar color = cv::Scalar(0, 0, 0);
        
        // the lines are outside of the image
        cv::line(padded, cv::Point(0, padding - 1), cv::Point(padded.cols - 1, padding - 1), color, thickness, cv::LINE_8); // top
        cv::line(padded, cv::Point(0, padded.rows - padding), cv::Point(padded.cols - 1, padded.rows - padding), color, thickness, cv::LINE_8); // bottom
        cv::line(padded, cv::Point(padding - 1, 0), cv::Point(padding - 1, padded.rows - 1), color, thickness, cv::LINE_8); // left
        cv::line(padded, cv::Point(padded.cols - padding, 0), cv::Point(padded.cols - padding, padded.rows - 1), color, thickness, cv::LINE_8); // right
    }

    return padded;
}