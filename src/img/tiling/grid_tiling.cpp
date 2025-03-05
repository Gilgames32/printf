#include "grid_tiling.hpp"
#include "tile.hpp"
#include "rotate.hpp"
#include <numeric>

size_t GridTiling::calc_waste(size_t document_width, size_t tile_width, size_t tile_height, size_t amount) {
    size_t columns = std::floor(document_width / tile_width);

    // the amount can be less than the number of columns
    return (document_width - tile_width * std::min(amount, columns)) * tile_height;
}

cv::Mat GridTiling::generate(const DocumentPreset& preset, std::vector<ImageSource *> images) {
    size_t document_width = preset.get_document_width_px();  // and take the gutter into account

    size_t tile_width = images[0]->get_width();
    size_t tile_height = images[0]->get_height();

    size_t quantity = std::accumulate(images.begin(), images.end(), 0, [](size_t sum, const ImageSource* img) {
        return sum + img->get_amount();
    });



    bool rotate = false;
    // fits both ways
    if (tile_width <= document_width && tile_height <= document_width) {
        // check which way causes less waste
        size_t waste_portrait = calc_waste(document_width, tile_width, tile_height, quantity);
        size_t waste_landscape = calc_waste(document_width, tile_height, tile_width, quantity);
        rotate = waste_landscape < waste_portrait;
    } else if (tile_width <= document_width) {
        rotate = false;
    } else if (tile_height <= document_width) {
        rotate = true;
    } else {
        // neither fits
        // TODO: handle this
        return cv::Mat();
    }

    if (rotate) {
        std::swap(tile_width, tile_height);
    }

    std::vector<Tile> tiles = {};
    for (ImageSource* img : images) {
        if (rotate) {
            img->add_filter(new RotateFilter());
        }
        // TODO
        // set the size of every image to match the first one
        // add gutter filter with guide parameter if the image doesnt already have one

        for (size_t i = 0; i < img->get_amount(); i++) {
            tiles.push_back(Tile(img));
        }
    }

    size_t columns = std::floor(document_width / tile_width);
    size_t rows = std::ceil((double)quantity / columns);
    size_t document_height = rows * tile_height;

    cv::Mat document = cv::Mat::ones(document_height, document_width, CV_8UC3);
    document.setTo(cv::Scalar(255, 255, 255));

    
    


    

    // TODO: corrected quantity

    for (size_t i = 0; i < quantity; i++) {
        Tile& tile = tiles[i];
        cv::Rect target_rect = cv::Rect((i % columns) * tile_width, (i / columns) * tile_height, tile_width, tile_height);

        tile.get_image().copyTo(document(target_rect));
    }

    return document;
}