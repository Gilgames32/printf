#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "filters/filter_store.hpp"

class ImgSource {
    /**
     * NOTE: maybe should store cv::Mat instead of img_path
     */
    std::string img_path;
    size_t amount;
    FilterStore filters;

  public:
    ImgSource(const cv::Mat& image, const size_t& amount, const FilterStore& fil);

    cv::Mat getImg() const;

    cv::Mat applyFilters() const;
};
