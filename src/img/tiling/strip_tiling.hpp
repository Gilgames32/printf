#include "tiling.hpp"
#include "tile.hpp"

enum class PriorityHeuristic { WIDTH, HEIGHT, DIAGONAL, AREA, ASPECT_RATIO };

class StripTiling : public Tiling {
  public:
    std::vector<std::shared_ptr<Tile>>& ph_sort(std::vector<std::shared_ptr<Tile>>& tiles, PriorityHeuristic heuristic = PriorityHeuristic::WIDTH);
    cv::Mat generate(const DocumentPreset& preset, std::vector<std::shared_ptr<ImageSource>> images) override;
};
