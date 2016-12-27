#ifndef NDK_PROGRAM_H
#define NDK_PROGRAM_H

#include <GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "VertexAttribute.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>

class Program {
public:

    Program();

    virtual ~Program();

    void use();

    void attachShader(const Shader &shader) const;

    void link();

    void assignUniform(std::string name, glm::tmat4x4<float> tmat4x4);

    void assignUniform(std::string name, glm::tmat3x3<float> tmat3x3);

    void assignUniform(std::string name, glm::tvec4<float> tvec4);

    void assignUniform(std::string name, glm::tvec3<float> tvec3);

    void assignUniform(std::string name, float val);

    void assignUniform(std::string name, int val);

    VertexAttribute assignAttribute(std::string entityKey, std::string name,
                                    int size,
                                    std::vector<float> &values);

private:
    GLuint program;
    std::map<std::string, GLuint *> vertexBuffers;
};


#endif //NDK_PROGRAM_H
