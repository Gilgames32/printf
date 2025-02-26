#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "cached_image.hpp"
#include "filters/filter.hpp"

class ImageSource : ICachableImage {
  private:
    cv::Mat original;
    CachedImage cached;
    size_t amount;
    std::vector<Filter*> filters;
    bool rotated;
    size_t width, height;

  public:
    ImageSource(cv::Mat source, size_t amount);

    ~ImageSource() { clear_filters(); }

    void add_filter(Filter* filter);

    void clear_filters();

    cv::Mat apply_filters() const;

    cv::Mat get_img() { return cached.get_img(); }

    size_t get_width() const { return width; }

    size_t get_height() const { return height; }

    size_t get_amount() const { return amount; }

    cv::Mat get_cachable() const override { return apply_filters(); }
};
