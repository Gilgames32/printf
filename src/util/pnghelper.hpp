#pragma once

#include <QImage>
#include <document_preset.hpp>
#include <exiv2/exiv2.hpp>

class PNGHelper {
  public:
    static void save_png(const std::string& path, const QImage& image, double dpi = 96.0);

    static void add_exif_data(const std::string& path, const DocumentPreset& properties);

    static Exiv2::ExifData generate_exif_data(const std::string& path, const DocumentPreset& properties);
};