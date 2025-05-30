#pragma once

namespace convert {

    inline double mm_to_pixel(double mm, double ppi) { return (mm / 25.4) * ppi; }

    inline double inch_to_pixel(double inch, double ppi) { return inch * ppi; }

    inline double pixel_to_mm(double pixel, double ppi) { return (pixel / ppi) * 25.4; }

    inline double ppi_to_ppm(double inch) { return inch / 0.0254; }

}  // namespace Convert