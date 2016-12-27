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
    renderBaseShape(polygon, GL_TRIANGLES, polygon.getToDraw());
}

void OpenGlShadowMapRenderer::renderBaseShape(BaseShape &shape, GLenum type, int count) const {
    program->use();
    auto position = program->assignAttribute(shape.getKey(), "vert", 3,
                                             shape.getVerticies());

    auto model = shape.getTransformation().modelMatrix();
    auto modelViewProjection = projection * shadowMapView * model;

    program->assignUniform("modelViewProjection", modelViewProjection);

    position.enable();

    glDrawArrays(type, 0, count);

    position.disable();
}

void OpenGlShadowMapRenderer::render(Plane &plane) {
    renderBaseShape(plane, GL_TRIANGLE_STRIP, plane.getVerticies().size() / 3);
}

void OpenGlShadowMapRenderer::render(Point &point) {
    //do not render points
}

glm::tmat4x4<float> OpenGlShadowMapRenderer::getProjectionView() {
    return projection * shadowMapView;
}

















