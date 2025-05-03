#include "image_source.hpp"

ImageSource::ImageSource(cv::Mat source, size_t amount)
    : original(source), amount(amount), cached(*this), filters(), rotated(false) {
    width = source.cols;
    height = source.rows;
}

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
