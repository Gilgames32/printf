#include "grid_tiling.hpp"

#include <numeric>

#include "padding.hpp"
#include "rotate.hpp"
#include "size.hpp"
#include "tile.hpp"
#include "convert.hpp"

int GridTiling::calc_waste(int document_width, int tile_width, int tile_height, int amount) {
    int columns = std::floor(static_cast<double>(document_width) / tile_width);
    int rows = std::ceil(static_cast<double>(amount) / columns);

    // the amount may not fill the last row completely
    if (amount < columns && rows == 1) {
        columns = amount;
    }

    return (document_width - tile_width * columns) * tile_height * rows;
}

cv::Mat GridTiling::generate(const DocumentPreset& preset, std::vector<std::shared_ptr<ImageSource>> images) {
    if (images.empty()) throw std::invalid_argument("No images provided");

    auto padding = preset.get_padding_px();
    auto ppi = preset.get_ppi();
    auto uniform_width_px = convert::mm_to_pixel(images[0]->width_mm, ppi);
    auto uniform_height_px = convert::mm_to_pixel(images[0]->height_mm, ppi);

    // set uniform sizes and padding
    for (auto img : images) {
        img->set_size_px(uniform_width_px, uniform_height_px, true);
        img->add_filter(std::make_shared<PaddingFilter>(padding, preset.get_guide(), preset.get_bleed_px(), preset.get_line_width()));
        img->burn();
    }

    // padding is added to every tile but its not needed on the sides
    // so extra padding is added to the document width, which is removed after tiling
    auto side_fix = std::max(padding - preset.get_line_width(), 0);
    auto document_width = preset.get_document_width_px() + 2 * side_fix;

    auto tile_width = images[0]->get_width_px();
    auto tile_height = images[0]->get_height_px();

    if (tile_width <= 0 || tile_height <= 0) {
        throw std::invalid_argument("Invalid image size");
    }

    
    // instantiate tiles based on amounts
    std::vector<Tile> tiles = {};
    for (auto img : images) {
        for (int i = 0; i < img->get_amount(); i++) {
            tiles.push_back(Tile(img));
        }
    }
    

    int quantity = static_cast<int>(tiles.size());
    int document_height = 0;
    std::cout << "\n\n";
    for (int i = 0; i < quantity;) {
        int x = 0;
        bool rotate_row = false;
        // fits both ways
        if (tile_width <= document_width && tile_height <= document_width) {
            // check which way causes less waste
            std::cout << "quantity: " << quantity << ", i: " << i << std::endl;
            auto waste_portrait = calc_waste(document_width, tile_width, tile_height, quantity - i);
            std::cout << "Waste portrait:  " << waste_portrait << std::endl;
            auto waste_landscape = calc_waste(document_width, tile_height, tile_width, quantity - i);
            std::cout << "Waste landscape: " << waste_landscape << std::endl;
            rotate_row = waste_landscape < waste_portrait;
        } else if (tile_width <= document_width) {
            rotate_row = false;
        } else if (tile_height <= document_width) {
            rotate_row = true;
        } else {
            // neither fits
            throw std::invalid_argument("Image does not fit in document");
        }

        int columns = std::floor(document_width / (rotate_row ? tile_height : tile_width));
        std::cout << "Columns: " << columns << std::endl;
        if (quantity - i < columns && preset.get_correct_quantity()) {
            int extra = columns - (quantity - i);
            for (int j = 0; j < extra; j++) {
                tiles.push_back(tiles[j]);
            }
            quantity += extra;
        }
        
        columns = std::min(columns, quantity - i);

        for (int j = 0; j < columns; j++) {
            Tile& tile = tiles[i + j];
            if (rotate_row != tile.is_rotated()) {
                tile.rotate();
            }
            tile.corner = cv::Point(x, document_height);
            x += tile.get_width();
        }

        document_height += rotate_row ? tile_width : tile_height;
        i += columns;
    }
    
    cv::Mat document = cv::Mat::ones(document_height, document_width, CV_8UC3);
    document.setTo(cv::Scalar(255, 255, 255));

    // copy tiles to document
    for (auto& tile : tiles) {
        cv::Rect target_rect = cv::Rect(tile.corner.x, tile.corner.y, tile.get_width(), tile.get_height());
        tile.get_image().copyTo(document(target_rect));
    }

    // remove padding from sides
    document = document(cv::Rect(side_fix, side_fix, document_width - 2 * side_fix, document_height - 2 * side_fix));

    return document;
}