#include <cups/cups.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "img/filters/mask.hpp"

using json = nlohmann::json;


int main(void) {
    // read an image
    cv::Mat image = cv::imread("./assets/3.png", 1);

    cv::Mat mask = cv::imread("./assets/mask.png", 1);

    MaskFilter maskFilter(mask);

    // create image window named "My Image"
    cv::namedWindow("My Image");

    // show the image on window
    cv::imshow("My Image", maskFilter.apply(image));

    // aboszolút filmszínház
    cv::waitKey(0);

    return 0;
}
