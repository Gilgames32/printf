#pragma once

#include "settings/document_presets.hpp"
#include "source.hpp"

namespace tiling {
    class Rect2D {
        const ImgSource& image;
        /**
         * TODO: Rewrite some parts of tiling.cpp because `primary_corner` changed
         * from a cv::Point to a vector of points
         */
        std::vector<std::pair<bool, cv::Point>> primary_corner;
        size_t amount_placed;

      public:
        size_t width, height;

        Rect2D(const ImgSource& img)
            : image(img), width(img.getImg().cols), height(img.getImg().rows), amount_placed(0) {}

        void rotate();

        size_t getSize() const { return width * height; }

        cv::Mat getImg() const { return image.getImg(); }

        bool moreRemaining() const { return amount_placed < image.getAmount(); }

        void place(const cv::Point& point, bool rotated) {
            primary_corner.push_back(std::make_pair(rotated, point));
            amount_placed++;
        }
    };

    namespace {
        void recursive_packing(std::vector<Rect2D> rects, cv::Point current_point,
                               size_t remainging_width, size_t current_height);

        std::pair<int, std::vector<Rect2D>> tile(std::vector<Rect2D> rects,
                                                 const DocumentPreset& preset);
    }  // namespace

    std::vector<Rect2D> generate(std::vector<const ImgSource&> images,
                                 const DocumentPreset& preset);
};  // namespace tiling
