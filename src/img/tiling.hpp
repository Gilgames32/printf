#pragma once

#include <opencv2/core/core.hpp>
#include <source.hpp>

struct document_preset {
    size_t document_width;
    size_t gutter_width;
    size_t tile_count;
    bool fill;
};

class tiling_generator {
    std::vector<img_source> imgs;
    document_preset user_preset;

   public:
    tiling_generator(const std::vector<img_source>& images, const document_preset& input_preset) {
        imgs = images;
        user_preset = input_preset;
    }

    /**
     * @brief Generates the tiling using TODO: some algorithm.
     *
     * @return cv::Mat The image data of the tiling.
     */
    cv::Mat static generate();
};
