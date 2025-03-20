#pragma once

#include <string>
#include <opencv2/opencv.hpp>

class InputFile {
private:
    std::string file_path;
    cv::Mat image;
    int amount;

public:
    explicit InputFile(const std::string& path);

    std::string get_file_name() const;

    std::string get_file_path() const;

    std::pair<int, int> get_image_size() const;

    cv::Mat get_image() const;

    int get_amount() const;

    void set_amount(int amount);
};