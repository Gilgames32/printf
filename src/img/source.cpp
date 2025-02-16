#include "source.hpp"

ImgSource::ImgSource(const cv::Mat &image, const FilterStore &fil) : file_data(image), filters(fil) {}

cv::Mat ImgSource::getImg() const { return file_data; }

cv::Mat ImgSource::applyFilters() const { return filters.applyAll(file_data); }
