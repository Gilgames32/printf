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
#include "document_preset.hpp"
#include "grid_tiling.hpp"
#include "padding.hpp"

int main(void) {
    DocumentPreset preset = DocumentPreset("./presets/document/tekercs.json");
    
    std::cout << preset.get_document_width_px() << std::endl;


    cv::Mat source = cv::imread("./assets/3.png");

    ImageSource img = ImageSource(source, 11);

    img.add_filter(new PaddingFilter(100, true));

    // img.add_filter(new RotateFilter());

    GridTiling tiling = GridTiling();
    cv::Mat result = tiling.generate(preset, {&img});


    cv::namedWindow("My Image", cv::WINDOW_AUTOSIZE | cv::WINDOW_GUI_NORMAL);
    cv::imshow("My Image", SizeFilter::resize_to_width(result, 1080));
    // cv::imshow("My Image", result);
    cv::waitKey(0);


    return 0;
}
