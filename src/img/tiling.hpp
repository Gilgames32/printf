#pragma once

#include "settings/document_presets.hpp"
#include "source.hpp"

namespace tiling {
    class Rect2D {
      public:
        const ImgSource& image;

        cv::Point primary_corner;

        size_t width, height;

        bool rotated = false;

        Rect2D(const ImgSource& img) : image(img), width(img.getImg().cols), height(img.getImg().rows) {}

        void rotate() {
            std::swap(width, height);
            rotated = !rotated;
        }

        size_t getArea() const { return width * height; }
    };

    void recursive_packing(std::vector<Rect2D> rects, cv::Point current_point, size_t remainging_width, size_t current_height);

    std::pair<int, std::vector<Rect2D>> tile(std::vector<Rect2D> rects, const DocumentPreset& preset);

    cv::Mat generate(std::vector<const ImgSource&> images, const DocumentPreset& preset);
};  // namespace tiling
