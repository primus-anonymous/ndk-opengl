#ifndef NDK_TEXTURE_H
#define NDK_TEXTURE_H

#include "Png.h"
#include <GLES2/gl2.h>

class Texture {

public:
    Texture();

    void from(const Png &png);

    void bindToUnit(GLenum unit);

    GLuint getGlTexture();

    static Texture *instance(const Png &png);

    virtual ~Texture();

private:
    GLuint texture;

};

#endif //NDK_TEXTURE_H
