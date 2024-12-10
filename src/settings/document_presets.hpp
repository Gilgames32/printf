#pragma once

#include <cstddef>

/*
gutter
margin
ppi
guide
min max height
*/

struct DocumentPreset {
    size_t document_width;
    size_t gutter_width;
    size_t tile_count;
    bool fill;
};
