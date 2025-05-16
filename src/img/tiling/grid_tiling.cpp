#include "grid_tiling.hpp"

#include <numeric>

#include "padding.hpp"
#include "rotate.hpp"
#include "size.hpp"
#include "tile.hpp"
#include "convert.hpp"

int GridTiling::calc_waste(int document_width, int tile_width, int tile_height, int amount) {
    int columns = std::floor(document_width / tile_width);

    // the amount can be less than the number of columns
    return (document_width - tile_width * std::min(amount, columns)) * tile_height;
}

cv::Mat GridTiling::generate(const DocumentPreset& preset, std::vector<std::shared_ptr<ImageSource>> images) {
    if (images.empty()) throw std::invalid_argument("No images provided");

    auto padding = preset.get_padding_px();
    auto ppi = preset.get_ppi();
    auto uniform_width_px = convert::mm_to_pixel(images[0]->width_mm, ppi);
    auto uniform_height_px = convert::mm_to_pixel(images[0]->height_mm, ppi);

    // set uniform sizes and padding
    for (auto img : images) {
        img->set_size_px(uniform_width_px, uniform_height_px);
        img->add_filter(std::make_shared<PaddingFilter>(padding, preset.get_guide()));
        img->burn();
    }

    // padding is added to every tile but its not needed on the sides
    // so extra padding is added to the document width, which is removed after tiling
    auto side_fix = padding - preset.get_line_width();
    auto document_width = preset.get_document_width_px() + 2 * side_fix;

    auto tile_width = images[0]->get_width_px();
    auto tile_height = images[0]->get_height_px();

    if (tile_width <= 0 || tile_height <= 0) {
        throw std::invalid_argument("Invalid image size");
    }

    auto quantity = std::accumulate(images.begin(), images.end(), 0,
                                    [](int sum, const std::shared_ptr<ImageSource> img) { return sum + img->get_amount(); });
    bool rotate = false;
    // fits both ways
    if (tile_width <= document_width && tile_height <= document_width) {
        // check which way causes less waste
        auto waste_portrait = calc_waste(document_width, tile_width, tile_height, quantity);
        auto waste_landscape = calc_waste(document_width, tile_height, tile_width, quantity);
        rotate = waste_landscape < waste_portrait;
    } else if (tile_width <= document_width) {
        rotate = false;
    } else if (tile_height <= document_width) {
        rotate = true;
    } else {
        // neither fits
        throw std::invalid_argument("Image does not fit in document");
    }

    // apply rotation
    if (rotate) {
        std::swap(tile_width, tile_height);
        for (auto img : images) {
            img->add_filter(std::make_shared<RotateFilter>());
        }
    }

    // instantiate tiles based on amounts
    std::vector<Tile> tiles = {};
    for (auto img : images) {
        for (int i = 0; i < img->get_amount(); i++) {
            tiles.push_back(Tile(img));
        }
    }

    // create document
    int columns = std::floor((double)document_width / tile_width);
    int rows = std::ceil((double)quantity / columns);
    int document_height = rows * tile_height;
    cv::Mat document = cv::Mat::ones(document_height, document_width, CV_8UC3);
    document.setTo(cv::Scalar(255, 255, 255));

    // copy tiles to document
    auto corrected_quantity = preset.get_correct_quantity() ? rows * columns : quantity;
    for (int i = 0; i < corrected_quantity; i++) {
        Tile& tile = tiles[i % quantity];
        cv::Rect target_rect = cv::Rect((i % columns) * tile_width, (i / columns) * tile_height, tile_width, tile_height);

        tile.get_image().copyTo(document(target_rect));
    }

    // remove padding from sides
    document = document(cv::Rect(side_fix, side_fix, document_width - 2 * side_fix, document_height - 2 * side_fix));

    return document;
}