#include "source.hpp"

ImgSource::ImgSource(const cv::Mat &image, const size_t& amount, const FilterStore &fil) : data(image), amount(amount), filters(fil) {}

cv::Mat ImgSource::apply_filters() { return filters.applyAll(data); }
