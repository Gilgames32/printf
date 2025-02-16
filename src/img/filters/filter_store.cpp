#include "filter_store.hpp"

void FilterStore::addFilter(Filter *filter) { filters.push_back(filter); }

cv::Mat FilterStore::applyAll(const cv::Mat &image) {
    cv::Mat result = image;
    for (auto filter : filters) {
        result = filter->apply(result);
    }
    clear_filters();
    return result;
}

FilterStore::~FilterStore() {
    clear_filters();
}

void FilterStore::clear_filters() {
    for (auto filter : filters) {
        delete filter;
    }
    filters.clear();
}
