#pragma once
#include "document_presets.hpp"
#include "source.hpp"

class Tiling {
  public:
    virtual cv::Mat generate(const DocumentPreset &preset, std::vector<ImgSource> images) = 0;
};

class Tile {
  public:
    ImgSource& image;

    cv::Point corner;

    size_t width, height;

    bool rotated = false;

    Tile(ImgSource& img) : image(img), width(img.get_width()), height(img.get_height()) {}

    void rotate() {
        std::swap(width, height);
        rotated = !rotated;
    }

    size_t getArea() const { return width * height; }
};