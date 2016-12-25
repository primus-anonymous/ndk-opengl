#include <shader/Shader.h>
#include <shader/Program.h>
#include "OpenGlSceneRenderer.h"

const glm::tmat4x4<float> OpenGlSceneRenderer::BIAS = {
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f};


void OpenGlSceneRenderer::render(Polygon &polygon) {

    Program *program = getPolygonProgram();
    program->use();

    auto position = program->assignAttributLocationShaderParam("vert", 3, polygon.getVerticies());
    auto norm = program->assignAttributLocationShaderParam("vertNormal", 3, polygon.getNormals());

    auto model = polygon.getTransformation().modelMatrix();

    auto modelView = view * model;
    auto modelViewProjection = projection * modelView;

    program->assignUniform("modelView", modelView);
    program->assignUniform("modelViewProjection", modelViewProjection);

    glm::tmat3x3<float> model3x3(modelView);

    program->assignUniform("normalMatrix", glm::transpose(glm::inverse(model3x3)));
    program->assignUniform("lighPos", glm::vec3(
            view * glm::vec4(light.getX(), light.getY(), light.getZ(), 1.0)));
    program->assignUniform("ambient", light.getAmbientComponent());
    program->assignUniform("specularExp", light.getSpecularExp());

    auto txt = program->assignAttributLocationShaderParam("textCoord", 2,
                                                          polygon.getTextureCoordinates());


    program->assignUniform("xPixelOffset", (float) (1.0 / shadowMap->getWidth()));
    program->assignUniform("yPixelOffset", (float) (1.0 / shadowMap->getHeight()));


    program->assignUniform("shadowMdelViewProjection",
                           BIAS * shadowMapMvp * polygon.getTransformation().modelMatrix());

    program->assignUniform("shadowTexture", 1);

    shadowMap->getTexture().bindToUnit(GL_TEXTURE1);

    std::vector<Texture *> textures = polygon.getTextures();

    for (int i = 0; i < textures.size(); i++) {

        textures[i]->bindToUnit(GL_TEXTURE0);

        program->assignUniform("texture", 0);

        glDrawArrays(GL_TRIANGLES, (polygon.getToDraw() / textures.size()) * i,
                     polygon.getToDraw() / textures.size());

    }

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(txt);
    glDisableVertexAttribArray(norm);

}


OpenGlSceneRenderer::OpenGlSceneRenderer(AssetsReader &assetsRe) : assetsReader(assetsRe) {

}

void OpenGlSceneRenderer::setView(const glm::tmat4x4<float> &view) {
    this->view = view;
}

void OpenGlSceneRenderer::setProjection(const glm::tmat4x4<float> &projection) {
    this->projection = projection;
}

void OpenGlSceneRenderer::setLight(const Light &l) {
    this->light = l;
}

void OpenGlSceneRenderer::render(Plane &plane) {

    Program *program = getPolygonProgram();
    program->use();

    auto position = program->assignAttributLocationShaderParam("vert", 3, plane.getVerticies());
    auto model = plane.getTransformation().modelMatrix();
    auto modelView = view * model;
    auto modelViewProjection = projection * modelView;
    auto norm = program->assignAttributLocationShaderParam("vertNormal", 3, plane.getNormals());

    program->assignUniform("modelView", modelView);
    program->assignUniform("modelViewProjection", modelViewProjection);

    glm::tmat3x3<float> model3x3(modelView);

    program->assignUniform("normalMatrix", glm::transpose(glm::inverse(model3x3)));
    program->assignUniform("lighPos", glm::vec3(
            view * glm::vec4(light.getX(), light.getY(), light.getZ(), 1.0)));
    program->assignUniform("ambient", light.getAmbientComponent());
    program->assignUniform("specularExp", light.getSpecularExp());

    auto txt = program->assignAttributLocationShaderParam("textCoord", 2,
                                                          plane.getTextureCoordinates());

    program->assignUniform("xPixelOffset", (float) (1.0 / shadowMap->getWidth()));
    program->assignUniform("yPixelOffset", (float) (1.0 / shadowMap->getHeight()));

    program->assignUniform("shadowMdelViewProjection",
                           BIAS * shadowMapMvp * plane.getTransformation().modelMatrix());

    program->assignUniform("texture", 0);
    program->assignUniform("shadowTexture", 1);

    plane.getTextures().front()->bindToUnit(GL_TEXTURE0);

    shadowMap->getTexture().bindToUnit(GL_TEXTURE1);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, plane.getVerticies().size() / 3);

    glDisableVertexAttribArray(position);
    glDisableVertexAttribArray(txt);
    glDisableVertexAttribArray(norm);

}

void OpenGlSceneRenderer::render(Point &point) {
    Program *program = getPointProgram();
    program->use();

    auto position = program->assignAttributLocationShaderParam("vert", 3, point.getVerticies());
    auto model = point.getTransformation().modelMatrix();
    auto modelView = view * model;
    auto modelViewProjection = projection * modelView;

    program->assignUniform("modelViewProjection", modelViewProjection);
    glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(position);


}

Program *OpenGlSceneRenderer::getPointProgram() {
    if (pointProgram == nullptr) {

        Shader vertexShader(GL_VERTEX_SHADER, assetsReader.readString("point_vertex.glsl").c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER,
                              assetsReader.readString("point_fragment.glsl").c_str());

        pointProgram = new Program();
        pointProgram->attachShader(vertexShader);
        pointProgram->attachShader(fragmentShader);
        pointProgram->link();
    }
    return pointProgram;
}

Program *OpenGlSceneRenderer::getPolygonProgram() {

    if (polygonProgram == nullptr) {
        Shader vertexShader(GL_VERTEX_SHADER,
                            assetsReader.readString("scene_vertex.glsl").c_str());
        Shader fragmentShader(GL_FRAGMENT_SHADER,
                              assetsReader.readString("scene_fragment.glsl").c_str());

        polygonProgram = new Program();
        polygonProgram->attachShader(vertexShader);
        polygonProgram->attachShader(fragmentShader);
        polygonProgram->link();
    }

    return polygonProgram;
}

OpenGlSceneRenderer::~OpenGlSceneRenderer() {
    if (polygonProgram != nullptr) {
        delete polygonProgram;
    }

    if (pointProgram != nullptr) {
        delete pointProgram;
    }

}

void OpenGlSceneRenderer::setShadowMap(ShadowMap *shadowMap) {
    this->shadowMap = shadowMap;
}

void OpenGlSceneRenderer::setShadowMapProjectionView(const glm::tmat4x4<float> &shadowMapMVp) {
    this->shadowMapMvp = shadowMapMVp;
}



















