#ifndef NDK_VBO_H
#define NDK_VBO_H

#include <GLES2/gl2.h>

class VertexAttribute {
public:

    VertexAttribute(GLint attr);

    void enable();

    void disable();

private:
    GLint attribute;
};


#endif //NDK_VBO_H
