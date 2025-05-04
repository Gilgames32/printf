#include "grid_tiling.hpp"

#include <numeric>

#include "padding.hpp"
#include "rotate.hpp"
#include "size.hpp"
#include "tile.hpp"
#include "convert.hpp"

size_t GridTiling::calc_waste(size_t document_width, size_t tile_width, size_t tile_height, size_t amount) {
    size_t columns = std::floor(document_width / tile_width);

    // the amount can be less than the number of columns
    return (document_width - tile_width * std::min(amount, columns)) * tile_height;
}

cv::Mat GridTiling::generate(const DocumentPreset& preset, std::vector<ImageSource*> images) {
    if (images.empty()) return cv::Mat();

    auto gutter = preset.get_gutter_px();
    auto ppi = preset.get_ppi();
    auto uniform_width_px = convert::mm_to_pixels(images[0]->width_mm, ppi);
    auto uniform_height_px = convert::mm_to_pixels(images[0]->height_mm, ppi);

    for (auto img : images) {
        img->set_size_px(uniform_width_px, uniform_height_px);
        img->add_filter(new PaddingFilter(gutter, preset.get_guide()));
        img->burn();
    }

    auto tile_width = images[0]->get_width_px();
    auto tile_height = images[0]->get_height_px();
    auto document_width = preset.get_document_width_px() + 2 * gutter;  // FIXME proper gutter, cut and add margin idk

    auto quantity = std::accumulate(images.begin(), images.end(), 0,
                                    [](size_t sum, const ImageSource* img) { return sum + img->get_amount(); });

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
        // TODO: handle this
        return cv::Mat();
    }

    if (rotate) {
        std::swap(tile_width, tile_height);
        for (auto img : images) {
            img->add_filter(new RotateFilter());
        }
    }

    std::vector<Tile> tiles = {};
    for (ImageSource* img : images) {
        for (size_t i = 0; i < img->get_amount(); i++) {
            tiles.push_back(Tile(img));
        }
    }

    size_t columns = std::floor(document_width / tile_width);  // TODO: test cast
    size_t rows = std::ceil((double)quantity / columns);
    size_t document_height = rows * tile_height;

    cv::Mat document = cv::Mat::ones(document_height, document_width, CV_8UC3);
    document.setTo(cv::Scalar(255, 255, 255));

    auto corrected_quantity = preset.get_correct_quantity() ? rows * columns : quantity;

    for (size_t i = 0; i < corrected_quantity; i++) {
        Tile& tile = tiles[i % quantity];
        cv::Rect target_rect = cv::Rect((i % columns) * tile_width, (i / columns) * tile_height, tile_width, tile_height);

        tile.get_image().copyTo(document(target_rect));
    }

    return document;
}