#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "filters/filter_store.hpp"

class ImgSource {
  public:
    cv::Mat data;
    FilterStore filters;
    size_t amount;

    ImgSource(const cv::Mat& image, const size_t& amount, const FilterStore& fil);

    size_t get_width() const { return data.cols; }

    size_t get_height() const { return data.rows; }

    cv::Mat apply_filters();
};
