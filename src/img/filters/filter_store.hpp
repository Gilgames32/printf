#pragma once

#include <vector>

#include "filter.hpp"

class FilterStore {
  private:
    std::vector<Filter *> filters;

  public:
    void addFilter(Filter *filter);

    cv::Mat applyAll(const cv::Mat &image) const;

    ~FilterStore();
};
