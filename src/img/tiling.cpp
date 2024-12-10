#include "tiling.hpp"

#include <opencv2/core/core.hpp>
#include <utility>

/**
 * @brief Based on the following paper: 10.1016/j.ipl.2015.08.008
 */
namespace tiling {
    void Rect2D::rotate() {
        size_t temp = width;
        width = height;
        height = temp;
        rotated = true;
    }

    namespace {
        void recursive_helper() {}

        std::pair<int, std::vector<Rect2D>> tile(std::vector<Rect2D> rects,
                                                 const DocumentPreset& preset,
                                                 bool widthSort = true) {
            /**
             * (1) Let D = 1, for each item, swap its width and height
             * if its width is larger than its height, sort all items by
             * non-increasing width H = 0, x = 0, y = 0.
             */
            bool rotation_allowed = true;  // D = 1
            int height_of_tiling = 0;      // H = 0

            int x, y = 0;

            std::for_each(rects.begin(), rects.end(), [&](Rect2D rect) {
                if (rect.width > rect.height) rect.rotate();
            });

            if (widthSort) {
                std::sort(rects.begin(), rects.end(),
                          [&](const Rect2D& a, const Rect2D& b) { return a.width > b.width; });
            } else {
                std::sort(rects.begin(), rects.end(),
                          [&](const Rect2D& a, const Rect2D& b) { return a.height > b.height; });
            }

            /**
             * (2) If h_{i} > W then x = w_{i} , y = H , w = W − w_{i} , h = h_{i} ,
             * H = H + h; otherwise, x = h_{i} , y = H , w = W − h_{i} ,
             * h = w_{i} , H = H + h.
             */
            int w, h;
            std::for_each(rects.begin(), rects.end(), [&](Rect2D rect) {
                y = height_of_tiling;
                if (rect.height > preset.document_width) {
                    x = rect.width;
                    w = preset.document_width - rect.width;
                    h = rect.height;
                } else {
                    x = rect.height;
                    w = preset.document_width - rect.height;
                    h = rect.width;
                }
                height_of_tiling += h;

                /**
                 * (3) RecursivePacking(x, y, w, h).
                 */
                recursive_helper(x, y, w, h);
            });

            /**
             * (4) If unpacked items remain, let B = B_{1} go to (2); otherwise stop.
             * TODO: figure this out
             */

            return std::make_pair(height_of_tiling, rects);
        }  // namespace

        cv::Mat generate(std::vector<const ImgSource&> images, const DocumentPreset& preset) {
            /**
             * @brief The authors of the algorithm sort the rectangles internally by
             * width. This is the most optimal for a lot of cases but not always. We
             * solve the problem with both width-sorting and height-sorting, and
             * compare the height of each, then return the smaller one.
             */

            /**
             * Create `Rect2D`-sform images
             */
            std::vector<Rect2D> rects = {};
            std::for_each(images.begin(), images.end(),
                          [&](const ImgSource& img) { rects.push_back(Rect2D(img)); });

            /**
             * Gutter stuff here
             */

            std::vector<Rect2D> rects_clone = rects;

            std::pair<int, std::vector<Rect2D>> width_sorting_height = tile(rects, preset);
            std::pair<int, std::vector<Rect2D>> height_sorting_height
                = tile(rects_clone, preset, false);

            int optimal_tiling_height
                = std::min(width_sorting_height.first, height_sorting_height.first);
            std::vector<Rect2D> optimal_tiling
                = width_sorting_height.first < height_sorting_height.first
                      ? width_sorting_height.second
                      : height_sorting_height.second;

            cv::Mat canvas = cv::Mat::zeros(optimal_tiling_height, preset.document_width, CV_8UC4);
            std::for_each(optimal_tiling.begin(), optimal_tiling.end(), [&](Rect2D rect) {
                auto image = rect.getImg();

                if (rect.isRotated()) {
                    cv::rotate(image, image, cv::ROTATE_90_COUNTERCLOCKWISE);
                }
                auto dstCoord = rect.getPrimaryCorner();
                auto dstRect = cv::Rect(dstCoord.x, dstCoord.y, rect.width, rect.height);

                image.copyTo(canvas(dstRect));
            });
        }
    }  // namespace
};  // namespace tiling
