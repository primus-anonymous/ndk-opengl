#include "Shader.h"

Shader::Shader(GLenum shaderType, const char *shaderCode) {
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw "Shader compilation failed!";
    }
}

Shader::~Shader() {
    glDeleteShader(shader);
}

GLuint Shader::getShader() const {
    return shader;
}
