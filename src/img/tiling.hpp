#pragma once

#include "settings/document_presets.hpp"
#include "source.hpp"

namespace tiling {
    class Rect2D {
        const ImgSource& image;
        cv::Point bottom_left_corner;
        bool rotated;

      public:
        size_t width, height;

        Rect2D(const ImgSource& img)
            : image(img), width(img.getImg().cols), height(img.getImg().rows), rotated(false) {}

        void rotate();

        bool isRotated() const { return rotated; }
    };

    namespace {
        void recursive_helper();

        std::pair<int, std::vector<Rect2D>> tile(std::vector<Rect2D> rects,
                                                 const DocumentPreset& preset,
                                                 bool widthSort = true);
    }  // namespace

    std::vector<Rect2D> generate(std::vector<const ImgSource&> images,
                                 const DocumentPreset& preset);
};  // namespace tiling
