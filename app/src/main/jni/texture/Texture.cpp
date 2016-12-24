#include <GLES2/gl2.h>
#include "Texture.h"

void Texture::bind(const Png &png) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
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


}

Texture::Texture() {

}

GLuint Texture::getGlTexture() {
    return texture;
}

Texture *Texture::boundInstance(const Png &png) {
    Texture *txt = new Texture();
    txt->bind(png);
    return txt;
}


