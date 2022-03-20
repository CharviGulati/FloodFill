#include "softBorderColorPicker.h"

SoftBorderColorPicker::SoftBorderColorPicker(unsigned int width, PNG &inputimage, double tol) {
    this->borderwidth = width;
    this->img = inputimage;
    this->tolerance = tol;
}

HSLAPixel SoftBorderColorPicker::operator()(point p) {
    int numPixels = 0;
    double totalH = 0.0;
    double totalS = 0.0;
    double totalL = 0.0;
    double totalA = 0.0;

    // if point p is within borderwidth distance away from any cell -  that is outside tolerance, then pixel at point p should be coloured/

    for (unsigned int x = p.x - borderwidth; x < p.x + borderwidth; x++) {
        for (unsigned int y = p.y - borderwidth; y < p.y + borderwidth; y++) {
            double euclidDist = (((p.y - y) * (p.y - y)) + ((p.x - x) * (p.x - x)));

            if (img.getPixel(x, y)->dist(p.c.color) > tolerance) { // This seems OK...?

                if (x < img.width() && y < img.height()) { // Ensure we don't access anything out of bounds

                    if (euclidDist < borderwidth * borderwidth) {
                        totalH += img.getPixel(x, y)->h;
                        totalS += img.getPixel(x, y)->s;
                        totalL += img.getPixel(x, y)->l;
                        totalA += img.getPixel(x, y)->a;
                        numPixels++;
                    }
                }
            }
        }
    }

    if (numPixels == 0) {
        return *img.getPixel(p.x, p.y);
    }

    return HSLAPixel(totalH / numPixels, totalS / numPixels, totalL / numPixels, totalA / numPixels);
}

/**
* SoftBorderColorPicker: a functor that determines the color that should be used
* given an `point`. If the given position is near a border of
* the fill, then it should be colored with the required color. Otherwise, its color
* should not change.
*
* The following criteria should be used to determine if a position p is near
* a border: if p is within distance `borderwidth` of any cell that will be outside the
* fill, then the pixel at position p should be colored with the average colour of
* pixels of the original image within `borderwidth` pixels of p.
*
* You will use Euclidian distance to judge proximity. That means if p is at
        * location (x,y), its distance to a point at location (a,b) is
        * squareRoot([(x-a)^2 + (y-b)^2]). Note that you should not ever have to
        * compute the square root to solve this problem.
*
**/


