#include <opencv2/core/core.hpp>
#include <utility>

#include "settings/document_presets.hpp"
#include "source.hpp"

/**
 * @brief Based on the following paper: 10.1016/j.ipl.2015.08.008
 */
namespace tiling {
    void recursive_helper();

    std::vector<std::pair<cv::Point, ImgSource>> generate(
        std::vector<const ImgSource&> images, const DocumentPreset& preset) {
        /**
         * @brief The authors of the algorithm sort the rectangles internally by
         * width. This is the most optimal for a lot of cases but not always. We
         * solve the problem with both width-sorting and height-sorting, and compare
         * the height of each, then return the smaller one.
         */

        /**
         * (1) Let D = 1, for each item, swap its width and height
         * if its width is larger than its height, sort all items by
         * non-increasing width, H = 0, x = 0, y = 0.
         */
        bool rotation_allowed = true;  // D = 1

        std::sort(images.begin(), images.end(),
                  [](const ImgSource& a, const ImgSource& b) {
                      return a.getImg().rows > b.getImg().rows;
                  });
    }
};  // namespace tiling
