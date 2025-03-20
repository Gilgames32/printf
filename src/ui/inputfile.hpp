#pragma once

#include <string>
#include <opencv2/opencv.hpp>

class InputFile {
private:
    std::string file_path;
    cv::Mat thumbnail;
    cv::Mat image;

public:
    explicit InputFile(const std::string& path);

    std::string get_file_name() const;

    std::string get_file_path() const;

    std::pair<int, int> get_image_size() const;

    cv::Mat get_thumbnail(int width, int height) const;

    cv::Mat get_image() const;
};