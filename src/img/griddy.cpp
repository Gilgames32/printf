#include <opencv2/core/core.hpp>
#include <vector>

struct preset {
    size_t document_width;
    size_t gutter_width;
    size_t tile_count;
    bool fill;
};

class TilingGenerator {
    std::vector<cv::Mat> imgs;
    preset user_preset;

   public:
    TilingGenerator(const std::vector<cv::Mat>& images, const preset& input_preset) {
        imgs = images;
        user_preset = input_preset;
    }

    /**
     * @brief Generates the tiling using TODO: some algorithm.
     *
     * @return cv::Mat The image data of the tiling.
     */
    cv::Mat static generate() {}
};
