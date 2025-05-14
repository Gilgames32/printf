#include "image_source.hpp"

#include <stdexcept>

ImageSource::ImageSource(cv::Mat source, size_t amount, double width_mm, double height_mm)
    : original(source),
      amount(amount),
      cached(*this),
      filters(),
      size_filter(SizeFilter(source.cols, source.rows)),
      width_mm(width_mm),
      height_mm(height_mm) {
    if (source.cols <= 0 || source.rows <= 0) throw std::invalid_argument("Invalid source");
    if (amount <= 0) throw std::invalid_argument("Invalid amount");
    if (width_mm <= 0) throw std::invalid_argument("Invalid width");
    if (height_mm <= 0) throw std::invalid_argument("Invalid height");
}

ImageSource::~ImageSource() { clear_filters(); }

void ImageSource::add_filter(IFilter* filter) {
    filters.push_back(filter);
    cached.set_dirty();
}

void ImageSource::clear_filters() {
    for (auto filter : filters) {
        delete filter;
    }
    filters.clear();
    cached.set_dirty();
}

cv::Mat ImageSource::apply_filters() const {
    cv::Mat image = original;
    image = size_filter.apply(image);
    for (auto filter : filters) {
        image = filter->apply(image);
    }
    return image;
}

cv::Mat ImageSource::burn() {
    original = apply_filters();
    clear_filters();
    size_filter.set_size(original.cols, original.rows);
    return get_img();
}

void ImageSource::set_size_px(int width, int height) {
    size_filter.set_size(width, height);
    cached.set_dirty();
}
