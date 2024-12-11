#include "tiling.hpp"

#include <opencv2/core/core.hpp>
#include <ranges>
#include <utility>

/**
 * @brief Based on the following paper (D. Zhang et al.): 10.1016/j.ipl.2015.08.008
 */
namespace tiling {
    void Rect2D::rotate() {
        size_t temp = width;
        width = height;
        height = temp;
        rotated = !rotated;
    }

    namespace {
        /**
         * @brief Recursive base case for `recursive_packing` function. Let `S` denote the area we
         * are tiling.
         *
         * @param rects The rectangles we are using for tiling
         * @param remainging_width Width of S
         * @param current_height Height of S
         * @return true If we have no more tiles to place, or S can't fit any that we can place.
         * @return false If we have even a single tile that can be placed and fits into S.
         */
        bool recursive_base_case(std::vector<Rect2D> rects, size_t remainging_width,
                                 size_t current_height) {}

        void recursive_packing(std::vector<Rect2D> rects, cv::Point current_point,
                               size_t remainging_width, size_t current_height) {
            if (recursive_base_case(rects, remainging_width, current_height)) return;

            std::vector<Rect2D> unplaced;
            std::ranges::copy_if(rects, std::back_inserter(unplaced),
                                 [](Rect2D rect) { return rect.moreRemaining(); });

            
        }

        /**
         * @brief NOTE: As per D. Zhang et al., the sorting of the rectangles can have a very big
         * effect on packing efficiency. On average, for our use case sorting by width performs
         * best, followed by area, perimeter, and finally height.
         *
         * Since there are so many heuristics which this function could take into consideration, it
         * is the duty of the caller to provide the sorting with which this function is to tile the
         * canvas.
         *
         * @param rects The rectangles to tile
         * @param preset Configurable document data
         * @return std::pair<int, std::vector<Rect2D>> The total height of the packing, and a vector
         * of rectangles which all have a position on the plane.
         */
        std::pair<int, std::vector<Rect2D>> tile(std::vector<Rect2D> rects,
                                                 const DocumentPreset& preset) {
            size_t height_of_tiling = 0;
            cv::Point current_point = cv::Point(0, 0);

            size_t remaining_width, current_height;

            for (auto&& rect : rects) {
                if (!rect.moreRemaining()) continue;

                current_point.y = height_of_tiling;

                rect.place(current_point);

                if (rect.height <= preset.document_width) rect.rotate();

                current_point.x = rect.width;
                remaining_width = preset.document_width - rect.width;
                current_height = rect.height;

                height_of_tiling += current_height;

                recursive_packing(rects, current_point, remaining_width, current_height);

                current_point.x = 0;
            }

            /**
             * (4) If unpacked items remain, let B = B_{1} go to (2); otherwise stop.
             */
            for (auto&& rect : rects) {
                if (rect.moreRemaining()) {
                    /**
                     * TODO: Figure this out.
                     */
                }
            }

            return std::make_pair(height_of_tiling, rects);
        }  // namespace

        cv::Mat generate(std::vector<const ImgSource&> images, const DocumentPreset& preset) {
            /**
             * Create `Rect2D`'s from images
             */
            std::vector<Rect2D> rects = {};
            std::for_each(images.begin(), images.end(),
                          [&](const ImgSource& img) { rects.push_back(Rect2D(img)); });

            /**
             * Gutter stuff here
             */

            /**
             * TODO: Expand heuristics for total area and perimeter
             * (and maybe even diagonal length).
             */
            std::pair<int, std::vector<Rect2D>> width_sorting = tile(rects, preset);
            std::vector<Rect2D> optimal_tiling = width_sorting.second;

            cv::Mat canvas = cv::Mat::zeros(width_sorting.first, preset.document_width, CV_8UC4);

            for (auto&& rect : optimal_tiling) {
                cv::Mat image = rect.getImg();

                if (rect.isRotated()) cv::rotate(image, image, cv::ROTATE_90_COUNTERCLOCKWISE);

                cv::Point dstCoord = rect.getPrimaryCorner();
                cv::Rect dstRect = cv::Rect(dstCoord.x, dstCoord.y, rect.width, rect.height);

                image.copyTo(canvas(dstRect));
            }
            return canvas;
        }
    }  // namespace
};  // namespace tiling
