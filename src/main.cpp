#include <cups/cups.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "img/filters/mask.hpp"
#include "img/tiling/grid_tiling.hpp"

//using json = nlohmann::json;


int main(void) {
    cv::Mat image = cv::imread("./assets/3.png", 1);

    GridTiling tiling = GridTiling();
    DocumentPreset preset = {1000, 10, true, true};
    std::vector<ImgSource> images = {ImgSource(image, FilterStore())};
    cv::Mat result = tiling.generate(preset, images);

    // create image window named "My Image"
    cv::namedWindow("My Image", cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);

    // show the image on window
    cv::imshow("My Image", result);

    // aboszolút filmszínház
    cv::waitKey(0);

    return 0;
}
