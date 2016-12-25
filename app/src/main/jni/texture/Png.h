#ifndef NDK_PNG_H
#define NDK_PNG_H

#include <vector>

extern "C" {
#include <png/png.h>
#include <setjmp.h>
}

class Png {
public:

    Png(const std::vector<char> &data, png_uint_32 glWidth, png_uint_32 glHeight, int bitDepth,
        int colorType);

    png_uint_32 getGlWidth() const;

    png_uint_32 getGlHeight() const;

    int getColorType() const;

    const char *getData() const;

private:
    png_uint_32 glWidth;
    png_uint_32 glHeight;
    int bitDepth;
    int colorType;
    std::vector<char> data; //данные RGB/RGBA

};

#endif //NDK_PNG_H
