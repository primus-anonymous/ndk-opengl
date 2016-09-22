#include "Png.h"

Png::Png(const std::vector<char> &data, png_uint_32 glWidth, png_uint_32 glHeight, int bitDepth,
         int colorType) {

    this->data = data;
    this->glWidth = glWidth;
    this->glHeight = glHeight;
    this->bitDepth = bitDepth;
    this->colorType = colorType;
}

png_uint_32 Png::getGlWidth() const {
    return this->glWidth;
}

png_uint_32 Png::getGlHeight() const {
    return this->glHeight;
}

int Png::getColorType() const {
    return this->colorType;
}

const char *Png::getData() const {
    return this->data.data();
}
