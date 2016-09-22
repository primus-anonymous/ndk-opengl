#ifndef NDK_SHADER_H
#define NDK_SHADER_H

#include <GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
    Shader(GLenum shaderType, const char *shaderCode);

    virtual ~Shader();

    GLuint getShader() const;

private:

    GLuint shader;
};


#endif //NDK_SHADER_H
