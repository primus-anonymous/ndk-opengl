#include "BaseShape.h"


BaseShape::~BaseShape() {
    for (auto *texture : textures) {
        delete texture;
    }
}

Transform &BaseShape::getTransformation() {
    return transform;
}

void BaseShape::addTexture(Texture *textures) {
    this->textures.push_back(textures);
}

BaseShape::BaseShape() {

}

std::vector<float> &BaseShape::getVerticies() {
    return verticies;
}

std::vector<float> &BaseShape::getNormals() {
    return normals;
}

std::vector<float> &BaseShape::getTextureCoordinates() {
    return uvs;
}

std::vector<Texture *> &BaseShape::getTextures() {
    return textures;
}

void BaseShape::addTexture(std::vector<Texture *> textures) {
    this->textures.insert(std::end(this->textures), std::begin(textures), std::end(textures));
}












