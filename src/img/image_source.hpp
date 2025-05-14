#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "cached_image.hpp"
#include "ifilter.hpp"
#include "icachable.hpp"
#include "size.hpp"

class ImageSource : ICachableImage {
  private:
    cv::Mat original;
    CachedImage cached;
    size_t amount;
    std::vector<IFilter*> filters;
    SizeFilter size_filter;

  public:
    double width_mm;
    double height_mm;
    ImageSource(cv::Mat source, size_t amount, double width_mm = 0, double height_mm = 0);

    virtual ~ImageSource();

    ImageSource(const ImageSource& other) = delete;

    void add_filter(IFilter* filter);

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
