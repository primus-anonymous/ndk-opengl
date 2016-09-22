#include <glm/gtc/matrix_transform.hpp>
#include "Transform.h"


Transform::Builder &Transform::Builder::translationX(float x) {
    outer.translationX = x;
    return *this;
}

Transform::Builder &Transform::Builder::translationY(float y) {
    outer.translationY = y;
    return *this;
}

Transform::Builder &Transform::Builder::translationZ(float z) {
    outer.translationZ = z;
    return *this;
}

Transform::Builder &Transform::Builder::rotationX(float x) {
    outer.angleX = x;
    return *this;
}

Transform::Builder &Transform::Builder::rotationY(float y) {
    outer.angleY = y;
    return *this;
}

Transform::Builder &Transform::Builder::rotationZ(float z) {
    outer.angleZ = z;
    return *this;
}

Transform::Builder &Transform::Builder::scaleX(float x) {
    outer.scaleX = x;
    return *this;
}

Transform::Builder &Transform::Builder::scaleY(float y) {
    outer.scaleY = y;
    return *this;

}

Transform::Builder &Transform::Builder::scaleZ(float z) {
    outer.scaleZ = z;
    return *this;

}

float Transform::getTranslationX() {
    return this->translationX;
}

float Transform::getTranslationY() {
    return this->translationY;
}

float Transform::getTranslationZ() {
    return this->translationZ;
}

float Transform::getRotationX() {
    return this->angleX;
}

float Transform::getRotationY() {
    return this->angleY;
}

float Transform::getRotationZ() {
    return this->angleZ;
}

float Transform::getScaleX() {
    return this->scaleX;
}

float Transform::getScaleY() {
    return this->scaleY;
}

float Transform::getScaleZ() {
    return this->scaleZ;
}


Transform::~Transform() {

}

Transform::Builder::Builder(Transform &transform) : outer(transform) {
}

Transform::Builder &Transform::builder() {
    return builderInstance;
}

void Transform::Builder::buildAsSRT() {
    glm::tmat4x4<float> translation = glm::translate(glm::tmat4x4<float>(1.0f),
                                                     glm::vec3(outer.translationX,
                                                               outer.translationY,
                                                               outer.translationZ));

    glm::tmat4x4<float> rotation(1.0f);

    rotation = glm::rotate(rotation, outer.angleX, glm::vec3(1.f, 0.f, 0.f));
    rotation = glm::rotate(rotation, outer.angleY, glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, outer.angleZ, glm::vec3(0.f, 0.f, 1.f));

    glm::tmat4x4<float> scale = glm::scale(glm::tmat4x4<float>(1.0f),
                                           glm::vec3(outer.scaleX, outer.scaleY, outer.scaleZ));

    outer.model = translation * rotation * scale;
}

void Transform::Builder::buildAsTRS() {
    glm::tmat4x4<float> translation = glm::translate(glm::tmat4x4<float>(1.0f),
                                                     glm::vec3(outer.translationX,
                                                               outer.translationY,
                                                               outer.translationZ));

    glm::tmat4x4<float> rotation(1.0f);

    rotation = glm::rotate(rotation, outer.angleX, glm::vec3(1.f, 0.f, 0.f));
    rotation = glm::rotate(rotation, outer.angleY, glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, outer.angleZ, glm::vec3(0.f, 0.f, 1.f));

    glm::tmat4x4<float> scale = glm::scale(glm::tmat4x4<float>(1.0f),
                                           glm::vec3(outer.scaleX, outer.scaleY, outer.scaleZ));

    outer.model = scale * rotation * translation;

}

void Transform::Builder::buildAsTSR() {
    glm::tmat4x4<float> translation = glm::translate(glm::tmat4x4<float>(1.0f),
                                                     glm::vec3(outer.translationX,
                                                               outer.translationY,
                                                               outer.translationZ));

    glm::tmat4x4<float> rotation(1.0f);

    rotation = glm::rotate(rotation, outer.angleX, glm::vec3(1.f, 0.f, 0.f));
    rotation = glm::rotate(rotation, outer.angleY, glm::vec3(0.f, 1.f, 0.f));
    rotation = glm::rotate(rotation, outer.angleZ, glm::vec3(0.f, 0.f, 1.f));

    glm::tmat4x4<float> scale = glm::scale(glm::tmat4x4<float>(1.0f),
                                           glm::vec3(outer.scaleX, outer.scaleY, outer.scaleZ));

    outer.model = rotation * scale * translation;

}

glm::tmat4x4<float> Transform::modelMatrix() {
    return model;
}

Transform::Transform() : builderInstance(*this) {

}
