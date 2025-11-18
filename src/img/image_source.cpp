#include "image_source.hpp"

#include <stdexcept>
#include "rotate.hpp"

ImageSource::ImageSource(cv::Mat source, int amount, double width_mm, double height_mm)
    : original(source),
      cached(*this),
      amount(amount),
      filters(),
      size_filter(SizeFilter(source.cols, source.rows)),
      rotate_filter(RotateFilter()),
      width_mm(width_mm),
      height_mm(height_mm) {
    if (source.cols <= 0 || source.rows <= 0) throw std::invalid_argument("Invalid source");
    if (amount <= 0) throw std::invalid_argument("Invalid amount");
    if (width_mm <= 0) throw std::invalid_argument("Invalid width");
    if (height_mm <= 0) throw std::invalid_argument("Invalid height");
}

ImageSource::~ImageSource() { clear_filters(); }

void ImageSource::add_filter(std::shared_ptr<IFilter> filter) {
    filters.push_back(filter);
    cached.set_dirty();
}

void ImageSource::clear_filters() {
    filters.clear();
    cached.set_dirty();
}

cv::Mat ImageSource::apply_filters() const {
    cv::Mat image = original;
    image = size_filter.apply(image);
    image = rotate_filter.apply(image);
    for (auto filter : filters) {
        image = filter->apply(image);
    }
    return image;
}

cv::Mat ImageSource::burn() {
    original = apply_filters();
    clear_filters();
    size_filter.set_size(original.cols, original.rows);
    rotate_filter.set_rotated(false);
    return get_img();
}

void ImageSource::set_size_px(int width, int height, bool auto_rotate) {
    if (auto_rotate && ((cached.get_width() > cached.get_height()) != (width > height))) {
        std::swap(width, height);
        set_rotated(true);
    }

    size_filter.set_size(width, height);
    cached.set_dirty();
}

void ImageSource::set_rotated(bool rotated) { 
    if (rotate_filter.get_rotated() == rotated) return;
    rotate_filter.set_rotated(rotated); 
    cached.set_dirty(); 
}
