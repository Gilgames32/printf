#pragma once

#include "image_source.hpp"

class Tile {
  private:
    ImageSource& image;
    size_t width, height;

  public:
    cv::Point corner;


    bool rotated = false;

    Tile(ImageSource& img) : image(img), width(img.get_width()), height(img.get_height()) {}

    void rotate() {
        std::swap(width, height);
        rotated = !rotated;
    }

    size_t get_area() const { return width * height; }

    size_t get_width() const { return width; }

    size_t get_height() const { return height; }

    cv::Mat get_image() { return image.get_img(); }
};
