#include "Program.h"

Program::Program() {
    program = glCreateProgram();
}

Program::~Program() {
    glDeleteProgram(program);

    for (auto it = vertexBuffers.begin(); it != vertexBuffers.end(); ++it) {
        glDeleteBuffers(1, (*it).second);
        delete (*it).second;
    }
    vertexBuffers.clear();
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

void Program::assignUniform(std::string name, glm::tmat4x4<float> tmat4x4) {

    GLint gvMvpHandler = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(gvMvpHandler, 1, false, glm::value_ptr(tmat4x4));

}

void Program::assignUniform(std::string name, glm::tvec4<float> tvec4) {
    GLint gvMvpHandler = glGetUniformLocation(program, name.c_str());
    glUniform4fv(gvMvpHandler, 1, glm::value_ptr(tvec4));
}

VertexAttribute Program::assignAttribute(std::string entityKey, std::string name, int size,
                                         std::vector<float> &values) {

    GLint gvPositionHandle = glGetAttribLocation(program, name.c_str());

    auto it = vertexBuffers.find(entityKey + name);

    GLuint *vertexBuffer;

    if (it != vertexBuffers.end()) {
        vertexBuffer = (*it).second;
    } else {
        vertexBuffer = new GLuint();
        glGenBuffers(1, vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * values.size(), values.data(), GL_STATIC_DRAW);
        vertexBuffers[entityKey + name] = vertexBuffer;
    }

    glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
    glVertexAttribPointer(gvPositionHandle, size, GL_FLOAT, GL_FALSE, 0, 0);

    return VertexAttribute(gvPositionHandle);
}


void Program::assignUniform(std::string name, glm::tvec3<float> tvec3) {
    GLint gvMvpHandler = glGetUniformLocation(program, name.c_str());
    glUniform3f(gvMvpHandler, tvec3[0], tvec3[1], tvec3[2]);

}

void Program::assignUniform(std::string name, glm::tmat3x3<float> tmat3x3) {
    GLint gvMvpHandler = glGetUniformLocation(program, name.c_str());
    glUniformMatrix3fv(gvMvpHandler, 1, false, glm::value_ptr(tmat3x3));
}

void Program::assignUniform(std::string name, float val) {
    GLint gvMvpHandler = glGetUniformLocation(program, name.c_str());
    glUniform1f(gvMvpHandler, val);
}

void Program::assignUniform(std::string name, int val) {
    GLint gvMvpHandler = glGetUniformLocation(program, name.c_str());
    glUniform1i(gvMvpHandler, val);
}




