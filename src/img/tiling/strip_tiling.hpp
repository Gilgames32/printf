#include "tiling.hpp"
#include "tile.hpp"

enum class PriorityHeuristic { WIDTH, HEIGHT, DIAGONAL, AREA, ASPECT_RATIO };

inline const char* to_string(PriorityHeuristic v)
{
    switch (v)
    {
        case PriorityHeuristic::WIDTH:     return "WIDTH";
        case PriorityHeuristic::HEIGHT:    return "HEIGHT";
        case PriorityHeuristic::DIAGONAL:  return "DIAGONAL";
        case PriorityHeuristic::AREA:      return "AREA";
        case PriorityHeuristic::ASPECT_RATIO: return "ASPECT_RATIO";
        default: return "UNKNOWN";
    }
}

class StripTiling : public Tiling {
  private:
    void recursive_packing(int x, int y, int row_width, int row_height, std::vector<Tile>& remaining, std::vector<Tile>& placed);
  public:
    std::vector<Tile>& ph_sort(std::vector<Tile>& tiles, PriorityHeuristic heuristic = PriorityHeuristic::WIDTH);
    cv::Mat generate(const DocumentPreset& preset, const std::vector<ImageSource*>& images) override;
};
