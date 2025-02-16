#include "filter_store.hpp"

void FilterStore::addFilter(Filter *filter) { filters.push_back(filter); }

cv::Mat FilterStore::applyAll(const cv::Mat &image) const {
    cv::Mat result = image;
    for (auto filter : filters) {
        result = filter->apply(result);
    }
    return result;
}

FilterStore::~FilterStore() {
    for (auto filter : filters) {
        delete filter;
    }
}
