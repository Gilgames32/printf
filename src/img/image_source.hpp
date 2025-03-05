#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "cached_image.hpp"
#include "icachable.hpp"
#include "filter.hpp"

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
    ImageSource(const ImageSource& other)
      : original(other.original),
        cached(*this),
        amount(other.amount),
        filters(other.filters), // FIXME
        rotated(other.rotated),
        width(other.width),
        height(other.height) {
          std::cout << "Copy constructor called" << std::endl;
        }

    void add_filter(Filter* filter);

    void clear_filters();

    cv::Mat apply_filters() const;

    cv::Mat get_img() { return cached.get_img(); }

    size_t get_width() const { return width; }

    size_t get_height() const { return height; }

    size_t get_amount() const { return amount; }

    cv::Mat get_cachable() const override { return apply_filters(); }
};
