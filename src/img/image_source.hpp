#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>

#include "cached_image.hpp"
#include "ifilter.hpp"
#include "icachable.hpp"
#include "size.hpp"

class ImageSource : ICachableImage {
  private:
    cv::Mat original;
    CachedImage cached;
    int amount;
    std::vector<std::shared_ptr<IFilter>> filters;
    SizeFilter size_filter;

  public:
    double width_mm;
    double height_mm;
    ImageSource(cv::Mat source, int amount, double width_mm = 0, double height_mm = 0);

    virtual ~ImageSource();

    ImageSource(const ImageSource& other) = delete;

    void add_filter(std::shared_ptr<IFilter> filter);

    void clear_filters();

    cv::Mat apply_filters() const;

    cv::Mat get_img() { return cached.get_img(); }

    int get_width_px() { return cached.get_width(); }

    int get_height_px() { return cached.get_height(); }

    void set_size_px(int width, int height);

    int get_amount() const { return amount; }

    cv::Mat get_cachable() const override { return apply_filters(); }

    cv::Mat burn();
};
