#include "mosaicColorPicker.h"

MosaicColorPicker::MosaicColorPicker(int mosaicwidth, PNG &inputimage) {
    this->width = mosaicwidth;
    this->img = inputimage;
    this->mosaicimg = img;
    double averageH;
    double averageS;
    double averageL;
    double averageA;

    int count = 0;
    for (int x = 0; x < img.width(); x += width) {
        for (int y = 0; y < img.height(); y += width) {
            count  = 0;
            double totalH = 0.0;
            double totalS = 0.0;
            double totalL = 0.0;
            double totalA = 0.0;

            for (int i = x; i < x + width; i++) {
                for (int j = y; j < y + width; j++) {
                    if (i < img.width() && j < img.height()) {
                        HSLAPixel *newPixel = mosaicimg.getPixel(i, j);
                        totalH += newPixel->h;
                        totalS += newPixel->s;
                        totalL += newPixel->l;
                        totalA += newPixel->a;
                        ++count;
                    }
                }
            }

            averageH = totalH / count;
            averageS = totalS / count;
            averageL = totalL / count;
            averageA = totalA / count;

            for (int a = x; a < x + width; a++) {
                for (int b = y; b < y + width; b++) {
                    if (a < img.width() && b < img.height()) {
                        HSLAPixel *newPixel = mosaicimg.getPixel(a, b);
                        newPixel->h = averageH;
                        newPixel->s = averageS;
                        newPixel->l = averageL;
                        newPixel->a = averageA;
                    }
                }
            }
        }
    }
}

HSLAPixel MosaicColorPicker::operator()(point p) {
    HSLAPixel *newPixel = mosaicimg.getPixel(p.x, p.y);
    return HSLAPixel(newPixel->h, newPixel->s, newPixel->l, newPixel->a);
}
