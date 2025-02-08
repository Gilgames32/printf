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
    ImgSource(const std::string& image_path, const size_t& amount, const FilterStore& filters)
        : img_path(image_path), amount(amount), filters(filters) {}

    cv::Mat getImg() const { return cv::imread(img_path, 1); }

    size_t getAmount() const { return amount; }
};
