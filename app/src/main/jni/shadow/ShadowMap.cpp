#include <exception>
#include "ShadowMap.h"
#include <stdexcept>


void ShadowMap::generateFbo() {

    // create a framebuffer object
    glGenFramebuffers(1, &fboId);

    // create render buffer and bind 16-bit depth buffer
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, shadowMapWidth, shadowMapHeight);

    // GL_LINEAR does not make sense for depth texture. However, next tutorial shows usage of GL_LINEAR and PCF. Using GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Remove artifact on the edges of the shadowmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    // Use a depth texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0,
                 GL_DEPTH_COMPONENT, GL_UNSIGNED_INT,
                 nullptr);

    // Attach the depth texture to FBO depth attachment point
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           texture.getGlTexture(), 0);


    // check FBO status
    int FBOstatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (FBOstatus != GL_FRAMEBUFFER_COMPLETE) {
        throw std::invalid_argument("GL_FRAMEBUFFER_COMPLETE failed, CANNOT use FBO");
    }

}

ShadowMap::ShadowMap(int width, int height) : shadowMapWidth(width),
                                              shadowMapHeight(height) {
    generateFbo();


}

GLuint ShadowMap::getFbo() {
    return fboId;
}

int ShadowMap::getWidth() {
    return shadowMapWidth;
}

int ShadowMap::getHeight() {
    return shadowMapHeight;
}

Texture &ShadowMap::getTexture() {
    return texture;
}

ShadowMap::~ShadowMap() {

    glDeleteBuffers(1, &fboId);
}

























