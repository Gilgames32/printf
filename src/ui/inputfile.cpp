#include "inputfile.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <stdexcept>

InputFile::InputFile(const std::string& path) : file_path(path) {
    if (file_path.rfind("file://", 0) == 0) {
        file_path = file_path.substr(7);
    }

    if (!std::filesystem::exists(file_path)) {
        throw std::invalid_argument("File does not exist: " + file_path);
    }

    image = cv::imread(file_path);
    if (image.empty()) {
        throw std::runtime_error("Failed to load image: " + file_path);
    }

    thumbnail = cv::Mat();
}

std::string InputFile::get_file_name() const {
    return std::filesystem::path(file_path).filename().string();
}

std::string InputFile::get_file_path() const {
    return file_path;
}

std::pair<int, int> InputFile::get_image_size() const {
    return std::make_pair(image.cols, image.rows);
}

cv::Mat InputFile::get_thumbnail(int width, int height) const {
    // regenerate thumbnail if size is different
    if (thumbnail.cols != width || thumbnail.rows != height) {
        cv::resize(image, thumbnail, cv::Size(width, height));
    }
    return thumbnail;
}

cv::Mat InputFile::get_image() const { return image; }
