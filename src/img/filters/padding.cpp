#include "padding.hpp"

PaddingFilter::PaddingFilter(int padding, bool guide, int bleed, int line_thickness, cv::Scalar line_color)
    : padding(padding), guide(guide), bleed(bleed), line_thickness(line_thickness), line_color(line_color) {}

cv::Mat PaddingFilter::apply(const cv::Mat &image) const {
    cv::Mat padded;
    auto expand = std::max(padding, (guide ? line_thickness : 0));

    if (expand > 0) {
        cv::copyMakeBorder(image, padded, expand, expand, expand, expand, cv::BORDER_CONSTANT, bg_color);
    } else {
        padded = image;
    }

    if (guide && line_thickness > 0) {
        int width = padded.cols;
        int height = padded.rows;

        int blep;
        if (bleed < 0) {
            blep = expand + std::max(width, height);
        } else {
            blep = expand + bleed;
        }

        auto lfx = (line_thickness + 1) / 2;
        // the lines are only outside of the image, show only on the gutter
        // top
        cv::line(padded, cv::Point(0, expand - lfx), cv::Point(blep - lfx, expand - lfx), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(width - 1 - blep + lfx, expand - lfx), cv::Point(width - 1, expand - lfx), line_color, line_thickness, cv::LINE_8);

        // bottom
        cv::line(padded, cv::Point(0, height - expand + lfx - 1), cv::Point(blep - lfx, height - expand + lfx - 1), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(width - 1 - blep + lfx, height - expand + lfx - 1), cv::Point(width - 1, height - expand + lfx - 1), line_color, line_thickness, cv::LINE_8);

        // left
        cv::line(padded, cv::Point(expand - lfx, 0), cv::Point(expand - lfx, blep - lfx), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(expand - lfx, height - 1 - blep + lfx), cv::Point(expand - lfx, height - 1), line_color, line_thickness, cv::LINE_8);

        // right
        cv::line(padded, cv::Point(width - 1 - expand + lfx, 0), cv::Point(width - 1 - expand + lfx, blep - lfx), line_color, line_thickness, cv::LINE_8);
        cv::line(padded, cv::Point(width - 1 - expand + lfx, height - 1 - blep + lfx), cv::Point(width - 1 - expand + lfx, height - 1), line_color, line_thickness, cv::LINE_8);
    }

    return padded;
}