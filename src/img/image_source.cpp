#include "image_source.hpp"

ImageSource::ImageSource(cv::Mat source, size_t amount, int width, int height)
    : original(source), amount(amount), cached(*this), filters(), size_filter(SizeFilter(width, height)) {}

void ImageSource::add_filter(Filter* filter) {
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
    return get_img();
}

void ImageSource::set_size(int width, int height) {
    size_filter.set_size(width, height);
    cached.set_dirty();
}
