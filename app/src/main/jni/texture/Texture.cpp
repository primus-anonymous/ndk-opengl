#include <GLES2/gl2.h>
#include "Texture.h"

void Texture::from(const Png &png) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (png.getColorType() == PNG_COLOR_TYPE_RGBA) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, png.getGlWidth(), png.getGlHeight(), 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, png.getData());
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, png.getGlWidth(), png.getGlHeight(), 0, GL_RGB,
                     GL_UNSIGNED_BYTE, png.getData());
    }

}

Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

Texture::Texture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}


Texture *Texture::instance(const Png &png) {
    Texture *txt = new Texture();
    txt->from(png);
    return txt;
}

void Texture::bindToUnit(GLenum unit) {
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

GLuint Texture::getGlTexture() {
    return texture;
}









