#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

glm::tmat4x4<float> Camera::getMatrix() {

    glm::tvec3<float> eye(viewAtX, viewAtY, viewAtZ + 8.f);

    glm::tvec3<float> center(0, 0, 0);
    glm::tvec3<float> up(0.f, 1.f, 0.f);

    return glm::lookAt(eye, center, up);
}

void Camera::setViewAtX(float x) {
    this->viewAtX = x;
}

float Camera::getViewAtX() {
    return viewAtX;
}

void Camera::setViewAtY(float y) {
    this->viewAtY = y;
}

float Camera::getViewAtY() {
    return viewAtY;
}

void Camera::setViewAtZ(float z) {
    this->viewAtZ = z;
}

float Camera::getViewAtZ() {
    return viewAtZ;
}
