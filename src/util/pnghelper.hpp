#include <QImage>

class PNGHelper {
public:
    static void save_png(const std::string& path, const QImage& image, double dpi = 96.0);
};