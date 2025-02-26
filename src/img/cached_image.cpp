#include "cached_image.hpp"

CachedImage::CachedImage(const ICachableImage& source) : source(source), isDirty(true) {}

cv::Mat CachedImage::get_img() { 
    if (isDirty) {
        cache = source.get_cachable();
        isDirty = false;
    }
    return cache;
}


void CachedImage::set_dirty() { isDirty = true; }