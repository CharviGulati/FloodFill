#include "negativeColorPicker.h"
#include <cmath>
NegativeColorPicker::NegativeColorPicker(PNG &inputimg) {
    this->img = inputimg;
}

/**
 * Picks the color for pixel (x, y), which is a member of point p.
 * The new color consists of components h, s, and l.
 * The saturation s is unchanged from the original color.
 *
 * The hue and luminance are inverted from the original image. Refer to HSLA documentation
 * to determine an "appropriate" meaning for hue/luminance inversion/negation.
 *
 * @return    The color chosen for (p).
 */
HSLAPixel NegativeColorPicker::operator()(point p) {
    HSLAPixel *px = this->img.getPixel(p.x, p.y);
    px->h = (int)(px->h + 180) % 360;
    // e.g. (360 + 180) mod 360 = 180, so starting from 360, we end with 180 which is opposite in a sense.
    px->l = 1 - px->l;
    //  1 - 0.33 = 0.67
    return *px;
}
