#pragma once

namespace convert {

    inline double mm_to_pixels(double mm, double ppi) { return (mm / 25.4) * ppi; }

    inline double inch_to_pixels(double inch, double ppi) { return inch * ppi; }

}  // namespace Convert