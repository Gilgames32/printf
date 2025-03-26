#include "image_source_view.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <stdexcept>

// TODO: dont hardcode the initial amount
ImageSourceView::ImageSourceView(const std::string& path) : file_path(path), amount(20) {
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

std::string ImageSourceView::get_file_name() const {
    return std::filesystem::path(file_path).filename().string();
}

std::string ImageSourceView::get_file_path() const {
    return file_path;
}

std::pair<int, int> ImageSourceView::get_image_size() const {
    return std::make_pair(image.cols, image.rows);
}

cv::Mat ImageSourceView::get_image() const { return image; }

int ImageSourceView::get_amount() const { return amount; }

void ImageSourceView::set_amount(int amount) { this->amount = amount; }