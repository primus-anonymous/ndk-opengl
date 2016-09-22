#include <glm/gtc/matrix_transform.hpp>
#include "BaseShape.h"

void BaseShape::setView(const glm::tmat4x4<float> &view) {
    this->view = view;
}

void BaseShape::setProjection(const glm::tmat4x4<float> &projection) {
    this->projection = projection;
}

BaseShape::~BaseShape() {
    for (auto *texture : textures) {
        delete texture;
    }
    delete program;
}

Transform &BaseShape::getTransformation() {
    return transform;
}

void BaseShape::addTexture(Texture *textures) {
    this->textures.push_back(textures);
}

BaseShape::BaseShape() {

}

void BaseShape::setVerticies(const std::vector<float> &verticies) {
    this->verticies = verticies;
}

void BaseShape::setNormals(const std::vector<float> &normals) {
    this->normals = normals;
}

void BaseShape::setTextureCoordinates(const std::vector<float> &textureCoordinates) {
    this->uvs = textureCoordinates;
}

void BaseShape::setLight(const Light &l) {
    this->light = l;
}


