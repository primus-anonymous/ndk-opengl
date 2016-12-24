#ifndef NDK_OPENGL_SHADOWMAP_H
#define NDK_OPENGL_SHADOWMAP_H


#include <GLES2/gl2.h>
#include <shader/Program.h>
#include <texture/AssetsReader.h>

class ShadowMap {
public:

    ShadowMap(int width, int height);

    GLuint getFbo();

    int getWidth();

    int getHeight();

    GLuint getTexture();

private:

    void generateFbo();

    int shadowMapWidth;
    int shadowMapHeight;
    GLuint fboId;
    GLuint renderTextureId;


};


#endif //NDK_OPENGL_SHADOWMAP_H
