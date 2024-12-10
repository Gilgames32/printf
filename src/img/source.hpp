#pragma once

#include <opencv2/core/core.hpp>

#include "filters/filter_store.hpp"

class ImgSource {
    /**
     * NOTE: It may be optimal to store the file path instead
     * of the file data.
     */
    cv::Mat file_data;
    size_t quantity;
    FilterStore filters;

  public:
    ImgSource(const cv::Mat& image, const size_t& amount, const FilterStore& fil)
        : file_data(image), quantity(amount), filters(fil) {}

    cv::Mat getImg() const { return file_data; }
};
