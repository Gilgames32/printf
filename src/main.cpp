#include <cups/cups.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using json = nlohmann::json;

cv::Mat generateGrid(const cv::Mat& image, int rows, int cols) {
    if (image.empty()) {
        throw std::runtime_error("Error: Image is empty!");
    }

    cv::Mat gridImage(image.rows * rows, image.cols * cols, image.type());

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cv::Rect cellRect(j * image.cols, i * image.rows, image.cols, image.rows);
            image.copyTo(gridImage(cellRect));
        }
    }

    return gridImage;
}

int main(void) {
    // read an image
    cv::Mat image = cv::imread("./assets/3.png", 1);
    std::cout << "Image size: " << image.size() << std::endl;
    std::cout << image.empty() << std::endl;
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", generateGrid(image, 4, 4));

    // aboszolút filmszínház
    cv::waitKey(0);

    return 0;
}
