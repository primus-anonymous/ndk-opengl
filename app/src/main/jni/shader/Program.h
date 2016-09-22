#ifndef NDK_PROGRAM_H
#define NDK_PROGRAM_H

#include <GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Program {
public:

    Program();

    virtual ~Program();

    void use();

    void attachShader(const Shader &shader) const;

    void link();

    void assignUniform(char const *name, glm::tmat4x4<float> tmat4x4);

    void assignUniform(char const *name, glm::tmat3x3<float> tmat3x3);

    void assignUniform(char const *name, glm::tvec4<float> tvec4);

    void assignUniform(char const *name, glm::tvec3<float> tvec3);

    void assignUniform(char const *name, float val);

    GLuint assignAttributLocationShaderParam(char const *name, int size, std::vector<float> &values);

    GLint getUniformShaderParam(char const * name);

    GLuint  getAttributePosition(char const * name);

    GLuint getProgram();

private:
    GLuint program;
};


#endif //NDK_PROGRAM_H
