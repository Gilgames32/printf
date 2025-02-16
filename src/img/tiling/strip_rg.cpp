#include "tiling.hpp"

#include <opencv2/core/core.hpp>
#include <ranges>
#include <utility>


namespace tiling {
    void Tile::rotate() {
        size_t temp = width;
        width = height;
        height = temp;
        rotated = !rotated;
    }

    /**
     * @brief Recursive base case for `recursive_packing` function. Let `S` denote the area we
     * are tiling.
     *
     * @param rects The rectangles we are using for tiling
     * @param s_width Width of S
     * @param s_height Height of S
     * @return true If we have no more tiles to place, or S can't fit any that we can place.
     * @return false If we have even a single tile that can be placed and fits into S.
     */
    bool recursive_base_case(std::vector<Tile> rects, size_t s_width, size_t s_height) {}

    void recursive_packing(std::vector<Tile> rects, cv::Point current_point, size_t s_width, size_t s_height) {
        recursive_base_case(rects, s_width, s_height);
    }

    /**
     * @param rects The rectangles to tile
     * @param preset Configurable document data
     * @return std::pair<int, std::vector<Tile>> The total height of the packing, and a vector
     * of rectangles which all have a position on the plane.
     */
    std::pair<int, std::vector<Tile>> tile(std::vector<Tile> rects, const DocumentPreset& preset) {
        size_t height_of_tiling = 0;
        cv::Point current_point = cv::Point(0, 0);

        size_t remaining_width, current_height;

        for (auto&& rect : rects) {
            current_point.y = height_of_tiling;

            rect.corner = current_point;

            if (rect.height <= preset.document_width_px) rect.rotate();

            current_point.x = rect.width;
            remaining_width = preset.document_width_px - rect.width;
            current_height = rect.height;

            height_of_tiling += current_height;

            recursive_packing(rects, current_point, remaining_width, current_height);

            current_point.x = 0;
        }

        return std::make_pair(height_of_tiling, rects);
    }

    cv::Mat generate(std::vector<const ImgSource&> images, const DocumentPreset& preset) {
        /**
         * Create `Tile`'s from images
         */
        std::vector<Tile> rects = {};
        std::for_each(images.begin(), images.end(), [&](const ImgSource& img) { rects.push_back(Tile(img)); });

        /**
         * Gutter stuff here
         */

        /**
         * TODO: Expand heuristics for total area 
         */
        std::pair<int, std::vector<Tile>> width_sorting = tile(rects, preset);
        std::vector<Tile> optimal_tiling = width_sorting.second;

        cv::Mat canvas = cv::Mat::zeros(width_sorting.first, preset.document_width_px, CV_8UC4);

        for (auto&& rect : optimal_tiling) {
            cv::Mat image = rect.image.get_img();

            if (rect.rotated) cv::rotate(image, image, cv::ROTATE_90_COUNTERCLOCKWISE);

            cv::Point dstCoord = rect.corner;
            cv::Rect dstRect = cv::Rect(dstCoord.x, dstCoord.y, rect.width, rect.height);

            image.copyTo(canvas(dstRect));
        }
        return canvas;
    }
};  // namespace tiling
