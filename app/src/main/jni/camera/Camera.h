#ifndef NDK_CAMERA_H
#define NDK_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>

class Camera {
public:
    glm::tmat4x4<float> getMatrix();

    void setViewAtX(float x);
    float getViewAtX();
    void setViewAtY(float y);
    float getViewAtY();
    void setViewAtZ(float z);
    float getViewAtZ();

private:

    float viewAtX = 0.0f;
    float viewAtY = 0.0f;
    float viewAtZ = 0.0f;
};

#endif //NDK_CAMERA_H
