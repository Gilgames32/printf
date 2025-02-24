#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "filter.hpp"
#include "cached_image.hpp"

class ImageSource {
  private:
    cv::Mat original;
    CachedImage cached;
    size_t amount;
    std::vector<Filter> filters;
    bool rotated;
    size_t width, height;

  public:
    ImageSource(cv::Mat source);

    void add_filter(const Filter& filter);

    void clear_filters();

    void apply_filters();

    cv::Mat get_img() const;

    size_t get_width() const;

    size_t get_height() const;

    size_t get_amount() const;
};
