#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "filters/filter_store.hpp"

class ImgSource {
    /**
     * NOTE: maybe should store cv::Mat instead of img_path
     */
    cv::Mat file_data;
    FilterStore filters;

  public:
    ImgSource(const cv::Mat& image, const FilterStore& fil);

    cv::Mat getImg() const;

    cv::Mat applyFilters() const;
};
