#include <cups/cups.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "image_source.hpp"
#include "rotate.hpp"
#include "size.hpp"

int main(void) {
    cv::Mat source = cv::imread("./assets/3.png", 1);

    ImageSource img = ImageSource(source, 1);

    img.add_filter(new RotateFilter());

    // create image window named "My Image"
    cv::namedWindow("My Image", cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);

    // show the image on window
    cv::imshow("My Image", SizeFilter::resize(img.get_img(), 800, 600));

    // aboszolút filmszínház
    cv::waitKey(0);

    return 0;
}
