#include "filter.hpp"
#include <opencv2/imgproc.hpp>

class SizeFilter : public Filter
{
private:
    static const int downScalingInterpolation = cv::INTER_AREA;
    static const int upScalingInterpolation = cv::INTER_CUBIC;
    int width;
    int height;
    bool isUniform;
public:
    SizeFilter(int width, int height);

    cv::Mat &apply(const cv::Mat &image) override;
};
