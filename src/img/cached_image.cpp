#include "cached_image.hpp"

CachedImage::CachedImage(const ICachableImage& source) : source(source), isDirty(true) {}

cv::Mat CachedImage::get_img() {
    regenerate();
    return cache;
}

void CachedImage::regenerate() {
    if (!isDirty) return;
    cache = source.get_cachable();
    isDirty = false;
}

int CachedImage::get_width() {
    regenerate();
    return cache.cols;
}

int CachedImage::get_height() {
    regenerate();
    return cache.rows;
}

void CachedImage::set_dirty() { isDirty = true; }