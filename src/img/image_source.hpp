#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "cached_image.hpp"
#include "filter.hpp"
#include "icachable.hpp"
#include "size.hpp"

class ImageSource : ICachableImage {
  private:
    cv::Mat original;
    CachedImage cached;
    size_t amount;
    std::vector<Filter*> filters;
    SizeFilter size_filter;

  public:
    double width_mm;
    double height_mm;
    ImageSource(cv::Mat source, size_t amount, double width_mm = 0, double height_mm = 0);

    virtual ~ImageSource() { clear_filters(); }
    ImageSource(const ImageSource& other)
        : original(other.original),
          cached(*this),
          amount(other.amount),
          filters(other.filters),  // FIXME
          size_filter(other.size_filter) {
        std::cout << "Copy constructor called" << std::endl;
    }

    void add_filter(Filter* filter);

    void clear_filters();

    cv::Mat apply_filters() const;

    cv::Mat get_img() { return cached.get_img(); }

    size_t get_width_px() { return cached.get_width(); }

    size_t get_height_px() { return cached.get_height(); }

    void set_size_px(int width, int height);

    size_t get_amount() const { return amount; }

    cv::Mat get_cachable() const override { return apply_filters(); }

    cv::Mat burn();
};
