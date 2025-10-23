#include "strip_tiling.hpp"

#include "padding.hpp"

std::vector<std::shared_ptr<Tile>>& StripTiling::ph_sort(std::vector<std::shared_ptr<Tile>>& tiles,
                                                         PriorityHeuristic heuristic) {
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
    // TODO: checks, check if it fits in any way, etc

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
    std::vector<std::shared_ptr<Tile>> remaining = {};
    for (auto tile : tiles) {
        for (int i = 0; i < tile->get_source()->get_amount(); i++) {
            remaining.push_back(std::make_shared<Tile>(*tile));
        }
    }

    // recursive strip packing
    int x = 0, y = 0;
    int total_height = 0;
    int row_width = 0, row_height = 0;
    auto side_fix = padding - preset.get_line_width();
    auto document_width = preset.get_document_width_px() + 2 * side_fix;

    std::vector<std::shared_ptr<Tile>> placed = {};

    while (!remaining.empty()) {
        auto tile = remaining.front();
        remaining.erase(remaining.begin());
        int tile_width = tile->get_width();
        int tile_height = tile->get_height();
        
        if (tile_height <= document_width) {
            tile->rotate();
            std::swap(tile_width, tile_height);
        }
        
        tile->corner = cv::Point(x, y);
        placed.push_back(tile);
        x = tile_width;
        y = total_height;
        total_height += tile_height;
        row_width = document_width - tile_width;
        row_height = tile_height;

        recursive_packing(x, y, row_width, row_height, remaining, placed);

        x = 0;
        y = total_height;
    }

    // find best heuristic

    // place tiles on the document

    cv::Mat document(total_height, document_width, CV_8UC3, cv::Scalar(255, 255, 255));
    for (auto tile : placed) {
        cv::Rect target_rect = cv::Rect(tile->corner.x, tile->corner.y, tile->get_width(), tile->get_height());
        
        tile->get_image().copyTo(document(target_rect));
    }
    document = document(cv::Rect(side_fix, side_fix, document_width - 2 * side_fix, total_height - 2 * side_fix));

    return document;
}

void StripTiling::recursive_packing(int x, int y, int row_width, int row_height, std::vector<std::shared_ptr<Tile>>& remaining, std::vector<std::shared_ptr<Tile>>& placed) {
    int priority = 5;
    int best_idx = -1;
    bool rotate = false;

    auto prio = [&](int width, int height, bool is_rotated, int idx) {
        if (priority > 1 && width == row_width && height == row_height) {
            priority = 1;
        }
        else if (priority > 2 && width == row_width && height <= row_height) {
            priority = 2;
        }
        else if (priority > 3 && width <= row_width && height == row_height) {
            priority = 3;
        }
        else if (priority > 4 && width <= row_width && height <= row_height) {
            priority = 4;
        }
        else {
            return;
        }
        best_idx = idx;
        rotate = is_rotated;
    };

    for (size_t i = 0; i < remaining.size(); i++) {
        auto tile = remaining[i];
        int tile_width = tile->get_width();
        int tile_height = tile->get_height();

        prio(tile_width, tile_height, false, i);
        prio(tile_height, tile_width, true, i);
    }

    if (priority >= 5 || best_idx < 0) {
        return;
    }

    auto tile = remaining[best_idx];
    remaining.erase(remaining.begin() + best_idx);

    if (rotate) tile->rotate();
    tile->corner = cv::Point(x, y);
    placed.push_back(tile);
    auto tile_width = tile->get_width();
    auto tile_height = tile->get_height();

    switch (priority)
    {
    case 2:
        recursive_packing(x, y + tile_height, row_width, row_height - tile_height, remaining, placed);
        break;
    case 3:
        recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
        break;
    case 4:
        int min_width = std::min_element(remaining.begin(), remaining.end(), [](const auto& a, const auto& b) {
            return a->get_width() < b->get_width();
        })->get()->get_width();
        
        int min_height = std::min_element(remaining.begin(), remaining.end(), [](const auto& a, const auto& b) {
            return a->get_height() < b->get_height();
        })->get()->get_height();

        // TODO: min_side?
        
        if (row_width - tile_width > min_width) {
            recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
        }
        else if (row_height - tile_height > min_height) {
            recursive_packing(x, y + tile_height, row_width, row_height - tile_height, remaining, placed);
        }
        else if (tile_width < min_width) {
            recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
            recursive_packing(x, y + tile_height, row_width, row_height - tile_height, remaining, placed);
        }
        else {
            recursive_packing(x, y + tile_height, tile_width, row_height - tile_height, remaining, placed);
            recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
        }
        break;
    }

}
