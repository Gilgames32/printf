#include "image_source_view.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <stdexcept>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

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

    width = image.cols;
    height = image.rows;
}

std::string ImageSourceView::get_file_name() const {
    return std::filesystem::path(file_path).filename().string();
}

std::string ImageSourceView::get_file_path() const {
    return file_path;
}

std::pair<int, int> ImageSourceView::get_image_resolution() const {
    return std::make_pair(image.cols, image.rows);
}

float ImageSourceView::get_image_aspect_ratio() const  {
    return float(image.cols) / float(image.rows);
}

std::pair<int, int> ImageSourceView::get_image_size() const { return std::make_pair(width, height); }

void ImageSourceView::set_image_size(int width, int height) {
    this->width = width;
    this->height = height;
    std::cout << "Image size set to: " << width << "x" << height << std::endl;
}

cv::Mat ImageSourceView::get_image() const { return image; }

int ImageSourceView::get_amount() const { return amount; }

void ImageSourceView::set_amount(int amount) { this->amount = amount; }

void ImageSourceView::load_from_preset(const std::string& preset_path) {
    std::cout << "Loading preset from: " << preset_path << std::endl;
       
    if (!std::filesystem::exists(preset_path)) {
        throw std::invalid_argument("Preset file does not exist: " + preset_path);
    }
    
    json json_data;
    std::ifstream file(preset_path);
    json_data = json::parse(file);
    file.close();

    width = json_data["width"];
    height = json_data["height"];
}
