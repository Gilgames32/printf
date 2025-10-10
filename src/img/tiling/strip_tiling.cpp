#include "strip_tiling.hpp"

#include "padding.hpp"

std::vector<std::shared_ptr<Tile>>& StripTiling::ph_sort(std::vector<std::shared_ptr<Tile>>& tiles, PriorityHeuristic heuristic) {
    // make every tile portrait
    for (auto tile : tiles) {
        if (tile->get_width() > tile->get_height()) {
            tile->rotate();
        }
    }

    switch (heuristic) {
        case PriorityHeuristic::WIDTH:
            std::sort(tiles.begin(), tiles.end(), [](const std::shared_ptr<Tile>& a, const std::shared_ptr<Tile>& b) {
                return a->get_width() > b->get_width();
            });
            break;

        default:
            break;
    }
    return tiles;
}

cv::Mat StripTiling::generate(const DocumentPreset& preset, std::vector<std::shared_ptr<ImageSource>> images) {
    /*
    if (images.empty()) throw std::invalid_argument("No images provided");

    // padding is added to every tile but its not needed on the sides
    // so extra padding is added to the document width, which is removed after tiling
    auto side_fix = padding - preset.get_line_width();
    auto document_width = preset.get_document_width_px() + 2 * side_fix;
    */

    auto ppi = preset.get_ppi();
    auto padding = preset.get_padding_px();

    // apply size and add padding
    for (auto img : images) {
        auto width_px = convert::mm_to_pixel(img->width_mm, ppi);
        auto height_px = convert::mm_to_pixel(img->height_mm, ppi);
        img->set_size_px(width_px, height_px, true);
        img->add_filter(std::make_shared<PaddingFilter>(padding, preset.get_guide(), padding));  // TODO configurable bleed
        img->burn();
    }

    // sort by priority heuristic
    std::vector<std::shared_ptr<Tile>> tiles = {};
    for (auto img : images) {
        tiles.push_back(std::make_shared<Tile>(img));
    }
    ph_sort(tiles);

    for (auto tile : tiles) {
        std::cout << "Tile: " << tile->get_width() << "x" << tile->get_height() << (tile->is_rotated() ? " (rotated)" : "") << std::endl;
    }

    // instantiate tiles based on amounts
    std::vector<std::shared_ptr<Tile>> instances = {};
    for (auto tile : tiles) {
        for (int i = 0; i < tile->get_source()->get_amount(); i++) {
            instances.push_back(std::make_shared<Tile>(*tile));
        }
    }

    // recursive strip packing
    int x = 0, y = 0;
    int current_row_height = 0;
    auto side_fix = padding - preset.get_line_width();
    auto document_width = preset.get_document_width_px() + 2 * side_fix;

    // find best heuristic

    // place tiles on the document

    return cv::Mat(100, 100, CV_8UC3, cv::Scalar(255, 255, 255));
}
