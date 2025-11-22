#include "image_source_view.hpp"

#include <filesystem>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <stdexcept>

#include "convert.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

ImageSourceView::ImageSourceView(): m_file_path(""), m_image(cv::Mat()), m_amount(1), m_width(0), m_height(0), mask_filter_view() {}

void ImageSourceView::load(const std::string& path, int amount, double ppi) {
    m_amount = amount;
    
    if (path.rfind("file://", 0) == 0) {
        m_file_path = path.substr(7);
    }
    else {
        m_file_path = path;
    }

    load_image(ppi);

    m_width = convert::pixel_to_mm(m_image.cols, ppi);
    m_height = convert::pixel_to_mm(m_image.rows, ppi);
}

void ImageSourceView::load_image(double ppi) {
    if (!std::filesystem::exists(m_file_path)) {
        throw std::invalid_argument("File does not exist: " + m_file_path);
    }
    
    m_image = cv::imread(m_file_path, cv::IMREAD_UNCHANGED);
    if (m_image.empty()) {
        throw std::runtime_error("Failed to load image: " + m_file_path);
    }

    convert_image();
}

void ImageSourceView::convert_image() {
    // blending to white if it has an alpha channel
    if ((m_image.type() == CV_8UC4) || (m_image.channels() == 4)) {
        // aplha blend to white
        cv::Mat bgr, alpha;
        std::vector<cv::Mat> channels;

        cv::split(m_image, channels);
        cv::merge(std::vector<cv::Mat>{channels[0], channels[1], channels[2]}, bgr);
        alpha = channels[3];

        bgr.convertTo(bgr, CV_32FC3, 1.0 / 255.0);
        alpha.convertTo(alpha, CV_32FC1, 1.0 / 255.0);

        cv::Mat alpha3c;
        cv::Mat alpha_array[] = {alpha, alpha, alpha};
        cv::merge(alpha_array, 3, alpha3c);

        cv::Mat white = cv::Mat(bgr.size(), CV_32FC3, cv::Scalar(1.0, 1.0, 1.0));

        cv::Mat blended;
        cv::multiply(alpha3c, bgr, bgr);
        cv::multiply(cv::Scalar(1.0, 1.0, 1.0) - alpha3c, white, white);
        cv::add(bgr, white, blended);

        blended.convertTo(m_image, CV_8UC3, 255.0);
    }

    if (m_image.type() != CV_8UC3) {
        m_image.convertTo(m_image, CV_8UC3);
    }
}

QString ImageSourceView::get_file_name() const {
    return QString::fromStdString(std::filesystem::path(m_file_path).filename().string());
}

QString ImageSourceView::get_file_path() const { return QString::fromStdString(m_file_path); }

QSize ImageSourceView::get_image_resolution() const { return QSize(m_image.cols, m_image.rows); }

double ImageSourceView::get_image_aspect_ratio() const { return float(m_image.cols) / float(m_image.rows); }

double ImageSourceView::get_width() const { return m_width; }

double ImageSourceView::get_height() const { return m_height; }

cv::Mat ImageSourceView::get_image() const { return m_image; }

void ImageSourceView::load_from_preset(const std::string& preset_path) {
    std::cout << "Loading preset from: " << preset_path << std::endl;

    if (!std::filesystem::exists(preset_path)) {
        throw std::invalid_argument("Preset file does not exist: " + preset_path);
    }

    json j;
    std::ifstream f(preset_path);
    j = json::parse(f);
    f.close();

    if (j.contains("amount")) {
        m_amount = j["amount"];
        emit amountChanged();
    }

    if (j.contains("width") && j.contains("height")) {
        int width = j["width"];
        int height = j["height"];
        if ((float(width) / float(height) >= 1.0) != (get_image_aspect_ratio() >= 1.0)) {
            std::swap(width, height);
        }
        m_width = width;
        m_height = height;
        emit widthChanged();
        emit heightChanged();
    }
}

std::shared_ptr<ImageSource> ImageSourceView::get_image_source(const DocumentPreset &preset) {
    auto img = std::make_shared<ImageSource>(m_image, m_amount, m_width, m_height);
    if (mask_filter_view.is_enabled()) img->add_filter(mask_filter_view.get_filter());
    return img;
}

void ImageSourceView::setPreset(const QString& presetPath) { load_from_preset(presetPath.toStdString()); }

void ImageSourceView::setSizeToWidth(double width, bool keepAspectRatio) {
    m_width = width;

    if (keepAspectRatio) m_height = width / get_image_aspect_ratio();

    std::cout << "Setting width to: " << m_width << std::endl;
    std::cout << "Setting height to: " << m_height << std::endl;
    emit widthChanged();
    emit heightChanged();
}

void ImageSourceView::setSizeToHeight(double height, bool keepAspectRatio) {
    m_height = height;

    if (keepAspectRatio) m_width = height * get_image_aspect_ratio();

    std::cout << "Setting width to: " << m_width << std::endl;
    std::cout << "Setting height to: " << m_height << std::endl;
    emit widthChanged();
    emit heightChanged();
}

Q_INVOKABLE MaskFilterView* ImageSourceView::get_mask_filter_view() { return &mask_filter_view; }
