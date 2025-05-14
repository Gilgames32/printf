#include "pnghelper.hpp"

#include <stdexcept>
#include "convert.hpp"
#include "spng.h"

// TODO: cleanup
void PNGHelper::save_png(const std::string& path, const QImage& image, double dpi) {
    if (image.format() != QImage::Format_RGB888) {
        throw std::runtime_error("Image format is not RGB888");
    }

    const int width = image.width();
    const int height = image.height();

    std::vector<uint8_t> raw;
    raw.reserve(width * height * 3);

    for (int y = 0; y < height; y++) {
        const uchar* scan = image.constScanLine(y);
        raw.insert(raw.end(), scan, scan + width * 3);
    }

    spng_ctx* ctx = spng_ctx_new(SPNG_CTX_ENCODER);
    if (!ctx) {
        throw std::runtime_error("Failed to create spng context");
    }

    FILE* file = fopen(path.c_str(), "wb");  // TODO: make cpp like
    if (!file) {
        spng_ctx_free(ctx);
        throw std::runtime_error("Failed to open file for writing");
    }

    spng_set_png_file(ctx, file);

    // header
    struct spng_ihdr ihdr = {};
    ihdr.width = width;
    ihdr.height = height;
    ihdr.bit_depth = 8;
    ihdr.color_type = SPNG_COLOR_TYPE_TRUECOLOR;  // No alpha channel
    ihdr.compression_method = 0;
    ihdr.filter_method = 0;
    ihdr.interlace_method = 0;

    if (spng_set_ihdr(ctx, &ihdr)) {
        fclose(file);
        spng_ctx_free(ctx);
        throw std::runtime_error("Failed to set IHDR chunk");
    }

    const uint32_t ppm = convert::ppi_to_ppm(dpi);

    struct spng_phys phys = {};
    phys.unit_specifier = 1;  // 1 = meters
    phys.ppu_x = ppm;         // Pixels per unit in X direction
    phys.ppu_y = ppm;         // Pixels per unit in Y direction

    if (spng_set_phys(ctx, &phys)) {
        fclose(file);
        spng_ctx_free(ctx);
        throw std::runtime_error("Failed to set PHYS chunk");
    }

    spng_set_option(ctx, SPNG_ENCODE_TO_BUFFER, 0);
    if (spng_encode_image(ctx, raw.data(), raw.size(), SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE)) {
        fclose(file);
        spng_ctx_free(ctx);
        throw std::runtime_error("Failed to encode image");
    }

    fclose(file);
    spng_ctx_free(ctx);
}

void PNGHelper::add_exif_data(const std::string& path, const DocumentPreset& properties) {
    auto image = Exiv2::ImageFactory::open(path);

    if (!image) {
        throw std::runtime_error("Failed to open image file.");
    }

    image->setExifData(generate_exif_data(path, properties));
    image->writeMetadata();
}

Exiv2::ExifData PNGHelper::generate_exif_data(const std::string& path, const DocumentPreset& properties) {
    auto ppi = Exiv2::Rational(properties.get_ppi(), 1);

    Exiv2::ExifData exif_data;
    exif_data["Exif.Image.ProcessingSoftware"] = "printf";
    exif_data["Exif.Image.XResolution"] = ppi;
    exif_data["Exif.Image.YResolution"] = ppi;
    exif_data["Exif.Image.ResolutionUnit"] = 2;  // inches

    return exif_data;
}