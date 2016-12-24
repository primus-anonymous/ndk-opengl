#include <stdexcept>
#include "OpenGlShadowMapRenderer.h"


OpenGlShadowMapRenderer::OpenGlShadowMapRenderer(AssetsReader &reader) {

    Shader vertexShader(GL_VERTEX_SHADER, reader.readString("depth_map_vertex.glsl").c_str());
    Shader fragmentShader(GL_FRAGMENT_SHADER, reader.readString("depth_map_fragment.glsl").c_str());

    program = new Program();
    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    program->link();

}

OpenGlShadowMapRenderer::~OpenGlShadowMapRenderer() {
    delete program;
}

void OpenGlShadowMapRenderer::setProjection(const glm::tmat4x4<float> &projection) {
    this->projection = projection;
}

void OpenGlShadowMapRenderer::setLight(const Light &l) {
    this->light = l;

    glm::tvec3<float> eye(light.getX(), light.getY(), light.getZ());

    glm::tvec3<float> center(light.getX(), -light.getY(), light.getZ());
    glm::tvec3<float> up(-light.getX(), 0, -light.getZ());

    shadowMapView = glm::lookAt(eye, center, up);

}

void OpenGlShadowMapRenderer::render(Polygon &polygon) {

    program->use();
    auto position = program->assignAttributLocationShaderParam("aShadowPosition", 3, polygon.getVerticies());

    auto model = polygon.getTransformation().modelMatrix();
    auto modelViewProjection = projection * shadowMapView * model;

    program->assignUniform("uMVPMatrix", modelViewProjection);

    glDrawArrays(GL_TRIANGLES, 0, polygon.getToDraw());
    glDisableVertexAttribArray(position);
}

void OpenGlShadowMapRenderer::render(Plane &plane) {
    program->use();
    auto position = program->assignAttributLocationShaderParam("aShadowPosition", 3, plane.getVerticies());

    auto model = plane.getTransformation().modelMatrix();
    auto modelViewProjection = projection * shadowMapView * model;

    program->assignUniform("uMVPMatrix", modelViewProjection);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, plane.getVerticies().size() / 3);
    glDisableVertexAttribArray(position);

}

void OpenGlShadowMapRenderer::render(Point &point) {
    //do not render points
}

glm::tmat4x4<float> OpenGlShadowMapRenderer::getMVP() {
    return projection * shadowMapView;
}

















