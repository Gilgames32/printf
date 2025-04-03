#pragma once

#include <string>
#include <opencv2/opencv.hpp>

class ImageSourceView {
private:
    std::string file_path;
    cv::Mat image;
    int amount;
    int width = 100;
    int height = 100;

public:
    explicit ImageSourceView(const std::string& path);

    std::string get_file_name() const;

    std::string get_file_path() const;

    std::pair<int, int> get_image_resolution() const;

    float get_image_aspect_ratio() const;

    std::pair<int, int> get_image_size() const;

    void set_image_size(int width, int height);

    cv::Mat get_image() const;

    int get_amount() const;

    void set_amount(int amount);

    void load_from_preset(const std::string& preset_path);
};