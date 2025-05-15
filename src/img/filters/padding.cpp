#include "padding.hpp"

PaddingFilter::PaddingFilter(size_t padding, bool guide, int bleed, int line_thickness, cv::Scalar line_color)
    : padding(padding), guide(guide), bleed(bleed), line_thickness(line_thickness), line_color(line_color) {}

cv::Mat PaddingFilter::apply(const cv::Mat &image) const {
    cv::Mat padded;
    if (padding > 0) {
        cv::copyMakeBorder(image, padded, padding, padding, padding, padding, cv::BORDER_CONSTANT, bg_color);
    } else {
        padded = image;
    }

    if (guide) {
        int width = padded.cols;
        int height = padded.rows;

        int blep;
        if (bleed < 0) {
            blep = padding + std::max(width, height);
        } else {
            blep = padding + bleed;
        }

        // the lines are only outside of the image, show only on the gutter
        // top
        cv::line(padded, cv::Point(0, padding - 1), cv::Point(blep - 1, padding - 1), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(width - blep, padding - 1), cv::Point(width - 1, padding - 1), line_color, line_thickness, cv::LINE_8);

        // bottom
        cv::line(padded, cv::Point(0, height - padding), cv::Point(blep - 1, height - padding), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(width - blep, height - padding), cv::Point(width - 1, height - padding), line_color, line_thickness, cv::LINE_8);

        // left
        cv::line(padded, cv::Point(padding - 1, 0), cv::Point(padding - 1, blep - 1), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(padding - 1, height - blep), cv::Point(padding - 1, height - 1), line_color, line_thickness, cv::LINE_8);

        // right
        cv::line(padded, cv::Point(width - padding, 0), cv::Point(width - padding, blep - 1), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(width - padding, height - blep), cv::Point(width - padding, height - 1), line_color, line_thickness, cv::LINE_8);
    }

    return padded;
}