#pragma once

#include "image_source.hpp"

class Tile {
  private:
    std::shared_ptr<ImageSource> image;
    int width, height;
    bool rotated = false;

  public:
    cv::Point corner;

    Tile(std::shared_ptr<ImageSource> img) : image(img), width(img->get_width_px()), height(img->get_height_px()), corner(cv::Point(0, 0)) {}
    Tile(const Tile& other) : image(other.image), width(other.width), height(other.height), rotated(other.rotated), corner(other.corner) {}

    void rotate() {
        std::swap(width, height);
        rotated = !rotated;
    }

    bool is_rotated() const { return rotated; }

    int get_area() const { return width * height; }

    int get_width() const { return width; }

    int get_height() const { return height; }

    int get_diagonal_suqared() const { return width * width + height * height; }

    int get_aspect_ratio() const { return (double) width / (double) height; }

    cv::Mat get_image() {
        image->set_rotated(rotated);
        return image->get_img(); 
    }

    std::shared_ptr<ImageSource> get_source() { return image; }
};
