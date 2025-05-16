#pragma once

#include "image_source.hpp"

class Tile {
  private:
    std::shared_ptr<ImageSource> image;
    int width, height;

  public:
    cv::Point corner;


    bool rotated = false;

    Tile(std::shared_ptr<ImageSource> img) : image(img), width(img->get_width_px()), height(img->get_height_px()) {}

    void rotate() {
        std::swap(width, height);
        rotated = !rotated;
    }

    int get_area() const { return width * height; }

    int get_width() const { return width; }

    int get_height() const { return height; }

    cv::Mat get_image() { return image->get_img(); }
};
