#ifndef NDK_OPENGL_SHADOWMAP_H
#define NDK_OPENGL_SHADOWMAP_H


#include <GLES2/gl2.h>
#include <texture/Texture.h>

class ShadowMap {
public:

    ShadowMap(int width, int height);

    GLuint getFbo();

    int getWidth();

    int getHeight();

    Texture& getTexture();

    virtual ~ShadowMap();

private:

    void generateFbo();

    int shadowMapWidth;
    int shadowMapHeight;
    GLuint fboId;
    Texture texture;

};


#endif //NDK_OPENGL_SHADOWMAP_H
