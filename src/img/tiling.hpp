#pragma once

#include <opencv2/core/core.hpp>
#include <source.hpp>

struct DocumentPreset {
    size_t document_width;
    size_t gutter_width;
    size_t tile_count;
    bool fill;
};

class TilingGenerator {
    std::vector<ImgSource> imgs;
    DocumentPreset user_preset;

   public:
    TilingGenerator(const std::vector<ImgSource>& images, const DocumentPreset& input_preset)
        : imgs(images),
          user_preset(input_preset) {}

    /**
     * @brief Generates the tiling using TODO: some algorithm.
     *
     * @return cv::Mat The image data of the tiling.
     */
    cv::Mat static generate();
};
