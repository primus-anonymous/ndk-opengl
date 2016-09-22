
#ifndef NDK_TEXTURE_H
#define NDK_TEXTURE_H

#include "Png.h"

class Texture {

public:
    Texture();
    void bind(const Png & png);
    virtual ~Texture();
    GLuint getGlTexture();
private:
    GLuint texture;

};

#endif //NDK_TEXTURE_H
