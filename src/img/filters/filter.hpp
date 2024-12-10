#include <opencv2/core/core.hpp>

class Filter
{
public:
    virtual cv::Mat &apply(const cv::Mat &) = 0;
};
