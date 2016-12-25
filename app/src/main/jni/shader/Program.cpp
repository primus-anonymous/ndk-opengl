#include "Program.h"

Program::Program() {
    program = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(program);
}

void Program::use() {
    glUseProgram(program);

}

void Program::attachShader(const Shader &shader) const {
    glAttachShader(program, shader.getShader());
}

void Program::link() {
    glLinkProgram(program);

    GLint success = 0;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        throw "Shader compilation failed!";
    }


}

void Program::assignUniform(const char *name, glm::tmat4x4<float> tmat4x4) {

    GLint gvMvpHandler = glGetUniformLocation(program, name);
    glUniformMatrix4fv(gvMvpHandler, 1, false, glm::value_ptr(tmat4x4));

}

void Program::assignUniform(char const *name, glm::tvec4<float> tvec4) {
    GLint gvMvpHandler = glGetUniformLocation(program, name);
    glUniform4fv(gvMvpHandler, 1, glm::value_ptr(tvec4));
}

GLuint Program::assignAttributLocationShaderParam(char const *name, int size,
                                                  std::vector<float> &values) {

    GLuint gvPositionHandle = glGetAttribLocation(program, name);
    glVertexAttribPointer(gvPositionHandle, size, GL_FLOAT, GL_FALSE, 0,
                          values.data());

    glEnableVertexAttribArray(gvPositionHandle);

    return gvPositionHandle;
}


void Program::assignUniform(char const *name, glm::tvec3<float> tvec3) {
    GLint gvMvpHandler = glGetUniformLocation(program, name);
    glUniform3f(gvMvpHandler, tvec3[0], tvec3[1], tvec3[2]);

}

void Program::assignUniform(char const *name, glm::tmat3x3<float> tmat3x3) {
    GLint gvMvpHandler = glGetUniformLocation(program, name);
    glUniformMatrix3fv(gvMvpHandler, 1, false, glm::value_ptr(tmat3x3));
}

void Program::assignUniform(char const *name, float val) {
    GLint gvMvpHandler = glGetUniformLocation(program, name);
    glUniform1f(gvMvpHandler, val);
}

void Program::assignUniform(char const *name, int val) {
    GLint gvMvpHandler = glGetUniformLocation(program, name);
    glUniform1i(gvMvpHandler, val);
}




