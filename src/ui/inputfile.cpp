#include "inputfile.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <stdexcept>

// TODO: dont hardcode the initial amount
InputFile::InputFile(const std::string& path) : file_path(path), amount(20) {
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

cv::Mat InputFile::get_image() const { return image; }

int InputFile::get_amount() const { return amount; }

void InputFile::set_amount(int amount) { this->amount = amount; }