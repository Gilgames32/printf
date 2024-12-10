#pragma once
#include <opencv2/imgproc.hpp>

#include "filter.hpp"

class SizeFilter : public Filter {
  private:
    static const int sizeInterDown = cv::INTER_AREA;
    static const int sizeInterUp = cv::INTER_CUBIC;
    int width;
    int height;
    bool lockAspect = true;

  public:
    SizeFilter(int width, int height);

    cv::Mat apply(const cv::Mat &image) override;

    static cv::Mat resize(const cv::Mat &image, int width, int height, int interDown = sizeInterDown,
                          int interUp = sizeInterUp);
};
