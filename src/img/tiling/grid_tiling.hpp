#pragma once
#include "tiling.hpp"

class GridTiling : public Tiling {
    // calculates the wasted area on the sides of the document
    size_t calc_waste(size_t document_width, size_t tile_width, size_t tile_height, size_t amount) {
        size_t columns = std::floor(document_width / tile_width);

        // the amount can be less than the number of columns
        return (document_width - tile_width * std::min(amount, columns)) * tile_height;
    }

  public:
    cv::Mat generate(const DocumentPreset& preset, const std::vector<ImgSource>& images) override {
        std::vector<Tile> tiles = {};
        std::for_each(images.begin(), images.end(), [&](const ImgSource& img) { tiles.push_back(Tile(img)); });
        // TODO
        // set the size of every image to match the first one
        // add gutter filter with guide parameter if the image doesnt already have one
        size_t document_width = preset.document_width_px;  // and take the gutter into account

        size_t tile_width = tiles[0].width;
        size_t tile_height = tiles[0].height;
        size_t quantity = tiles.size();

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
            std::for_each(tiles.begin(), tiles.end(), [](Tile& tile) { tile.rotate(); });
            std::swap(tile_width, tile_height);
        }

        size_t columns = std::floor(document_width / tile_width);
        size_t rows = std::ceil(quantity / columns);
        size_t document_height = rows * tile_height;

        cv::Mat document = cv::Mat::zeros(document_height, document_width, CV_8UC3);

        // TODO: corrected quantity

        for (size_t i = 0; i < quantity; i++) {
            Tile& tile = tiles[i];
            cv::Rect target_rect = cv::Rect((i % columns) * tile_width, (i / columns) * tile_height, tile_width, tile_height);
            tile.image.getImg().copyTo(document(target_rect));
        }

        return document;
    }
};