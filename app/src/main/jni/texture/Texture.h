
#ifndef NDK_TEXTURE_H
#define NDK_TEXTURE_H

#include "Png.h"
#include <GLES2/gl2.h>

class Texture {

public:
    Texture();
    void bind(const Png & png);
    virtual ~Texture();
    GLuint getGlTexture();

    static Texture * boundInstance(const Png &png);

private:
    GLuint texture;

};

#endif //NDK_TEXTURE_H
