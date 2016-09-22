#include "Point.h"

Point::~Point() {

}

Point::Point(AssetsReader &reader) {
    Shader vertexShader(GL_VERTEX_SHADER, reader.readString("point_vertex.glsl").c_str());
    Shader fragmentShader(GL_FRAGMENT_SHADER, reader.readString("point_fragment.glsl").c_str());

    program = new Program();
    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    program->link();

    verticies.push_back(0);
    verticies.push_back(0);
    verticies.push_back(0);
}

void Point::draw() {
    program->use();

    auto position = program->assignAttributLocationShaderParam("vert", 3, verticies);
    auto model = transform.modelMatrix();
    auto modelView = view * model;
    auto modelViewProjection = projection * modelView;

    program->assignUniform("modelViewProjection", modelViewProjection);
    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(position);
}
