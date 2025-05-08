#pragma once
#include <opencv2/imgproc.hpp>

#include "ifilter.hpp"

class SizeFilter : public IFilter {
  private:
    static const int sizeInterDown = cv::INTER_AREA;
    static const int sizeInterUp = cv::INTER_CUBIC;

    int width;
    int height;

  public:
    SizeFilter(int width, int height);

    void set_size(int width, int height);

    cv::Mat apply(const cv::Mat &image) const override;

    static cv::Mat resize(const cv::Mat &image, int width, int height, int interDown = sizeInterDown,
                          int interUp = sizeInterUp);

    static cv::Mat resize_to_width(const cv::Mat &image, int width, int interDown = sizeInterDown, int interUp = sizeInterUp);
};
