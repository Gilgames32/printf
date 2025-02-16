#pragma once
#include "document_presets.hpp"
#include "source.hpp"

class Tiling {
  public:
    virtual cv::Mat generate(const DocumentPreset &preset, const std::vector<ImgSource> &images) = 0;
};

class Tile {
  public:
    const ImgSource& image;

    cv::Point corner;

    size_t width, height;

    bool rotated = false;

    Tile(const ImgSource& img) : image(img), width(img.getImg().cols), height(img.getImg().rows) {}

    void rotate() {
        std::swap(width, height);
        rotated = !rotated;
    }

    size_t getArea() const { return width * height; }
};