#include "strip_tiling.hpp"

#include "padding.hpp"

std::vector<Tile>& StripTiling::ph_sort(std::vector<Tile>& tiles, PriorityHeuristic heuristic) {
    // make every tile portrait
    for (auto tile : tiles) {
        if (tile.get_width() > tile.get_height()) {
            tile.rotate();
        }
    }

    using SortPredicate = bool (*)(const Tile&, const Tile&);

    SortPredicate predicate = [&]() -> SortPredicate {
        switch (heuristic) {
            case PriorityHeuristic::WIDTH:
                return [](const Tile& a, const Tile& b) { return a.get_width() > b.get_width(); };
            case PriorityHeuristic::HEIGHT:
                return [](const Tile& a, const Tile& b) { return a.get_height() > b.get_height(); };
            case PriorityHeuristic::DIAGONAL:
                return [](const Tile& a, const Tile& b) { return a.get_diagonal_suqared() > b.get_diagonal_suqared(); };
            case PriorityHeuristic::AREA:
                return [](const Tile& a, const Tile& b) { return a.get_area() > b.get_area(); };
            case PriorityHeuristic::ASPECT_RATIO:
                return [](const Tile& a, const Tile& b) { return a.get_aspect_ratio() > b.get_aspect_ratio(); };
            // We return false to satisfy the strict weak ordering requirement for the predicate.
            default:
                return [](const Tile& a, const Tile& b) { return false; };
        }
    }();

    std::sort(tiles.begin(), tiles.end(), predicate);

    return tiles;
}

cv::Mat StripTiling::generate(const DocumentPreset& preset, const std::vector<ImageSource*>& images) {
    /*
    if (images.empty()) throw std::invalid_argument("No images provided");
    // TODO: checks, check if it fits in any way, etc
    */

    auto ppi = preset.get_ppi();
    auto padding = preset.get_padding_px();
    auto side_fix = padding - preset.get_line_width();
    auto document_width = preset.get_document_width_px() + 2 * side_fix;

    // apply size and add padding
    for (const auto& img : images) {
        auto width_px = convert::mm_to_pixel(img->width_mm, ppi);
        auto height_px = convert::mm_to_pixel(img->height_mm, ppi);
        img->set_size_px(width_px, height_px, true);
        img->add_filter(
            std::make_shared<PaddingFilter>(padding, preset.get_guide(), preset.get_bleed_px(), preset.get_line_width()));
        img->burn();
    }

    int min_total_height = std::numeric_limits<int>::max();
    PriorityHeuristic best_heuristic;
    std::vector<Tile> best_placement = {};

    for (auto heuristic : {
             PriorityHeuristic::WIDTH,
             PriorityHeuristic::HEIGHT,
             PriorityHeuristic::DIAGONAL,
             PriorityHeuristic::AREA,
             // PriorityHeuristic::ASPECT_RATIO
         }) {
        // sort by priority heuristic
        std::vector<Tile> tiles;
        tiles.reserve(images.size());

        for (const auto& img : images) {
            tiles.emplace_back(Tile(img));
        }

        ph_sort(tiles, heuristic);

        // instantiate tiles based on amounts
        std::vector<Tile> remaining;
        // Assuming that on average, each image is printed three times
        remaining.reserve(images.size() * 3);

        for (const auto& tile : tiles) {
            for (int i = 0; i < tile.get_source()->get_amount(); i++) {
                remaining.push_back(tile);
            }
        }

        // recursive strip packing
        int x = 0, y = 0;
        int total_height = 0;
        int row_width = 0, row_height = 0;

        std::vector<Tile> placed;
        placed.reserve(images.size());

        while (!remaining.empty()) {
            auto tile = remaining.front();
            remaining.erase(remaining.begin());
            int tile_width = tile.get_width();
            int tile_height = tile.get_height();

            if (tile_height <= document_width) {
                tile.rotate();
                std::swap(tile_width, tile_height);
            }

            tile.corner = cv::Point(x, y);
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

        if (total_height < min_total_height) {
            min_total_height = total_height;
            best_placement = placed;
            best_heuristic = heuristic;
        }
    }
    std::cout << "Best heuristic: " << to_string(best_heuristic) << " with height " << min_total_height << std::endl;

    // place tiles on the document
    auto document_height = min_total_height;
    cv::Mat document(document_height, document_width, CV_8UC3, cv::Scalar(255, 255, 255));

    for (auto& tile : best_placement) {
        cv::Rect target_rect = cv::Rect(tile.corner.x, tile.corner.y, tile.get_width(), tile.get_height());

        tile.get_image().copyTo(document(target_rect));
    }

    document = document(cv::Rect(side_fix, side_fix, document_width - 2 * side_fix, document_height - 2 * side_fix));

    return document;
}

void StripTiling::recursive_packing(int x, int y, int row_width, int row_height, std::vector<Tile>& remaining,
                                    std::vector<Tile>& placed) {
    int priority = 5;
    int best_idx = -1;
    bool rotate = false;

    auto prio = [&](int width, int height, bool is_rotated, int idx) {
        if (priority > 1 && width == row_width && height == row_height) {
            priority = 1;
        } else if (priority > 2 && width == row_width && height <= row_height) {
            priority = 2;
        } else if (priority > 3 && width <= row_width && height == row_height) {
            priority = 3;
        } else if (priority > 4 && width <= row_width && height <= row_height) {
            priority = 4;
        } else {
            return;
        }
        best_idx = idx;
        rotate = is_rotated;
    };

    for (size_t i = 0; i < remaining.size(); i++) {
        const auto& tile = remaining[i];
        int tile_width = tile.get_width();
        int tile_height = tile.get_height();

        prio(tile_width, tile_height, false, i);
        prio(tile_height, tile_width, true, i);
    }

    if (priority >= 5 || best_idx < 0) {
        return;
    }

    auto tile = remaining[best_idx];
    remaining.erase(remaining.begin() + best_idx);

    if (rotate) tile.rotate();

    tile.corner = cv::Point(x, y);
    placed.push_back(tile);

    auto tile_width = tile.get_width();
    auto tile_height = tile.get_height();

    switch (priority) {
        case 2:
            recursive_packing(x, y + tile_height, row_width, row_height - tile_height, remaining, placed);
            break;
        case 3:
            recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
            break;
        case 4:
            int min_side = std::numeric_limits<int>::max();
            for (auto t : remaining) {
                min_side = std::min({min_side, t.get_width(), t.get_height()});
            }

            if (row_width - tile_width < min_side) {
                recursive_packing(x, y + tile_height, row_width, row_height - tile_height, remaining, placed);
            } else if (row_height - tile_height < min_side) {
                recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
            } else if (tile_width < min_side) {
                recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
                recursive_packing(x, y + tile_height, row_width, row_height - tile_height, remaining, placed);
            } else {
                recursive_packing(x, y + tile_height, tile_width, row_height - tile_height, remaining, placed);
                recursive_packing(x + tile_width, y, row_width - tile_width, row_height, remaining, placed);
            }
            break;
    }
}
