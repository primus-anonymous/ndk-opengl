#ifndef NDK_ISHAPE_H
#define NDK_ISHAPE_H

#include <glm/detail/type_mat4x4.hpp>
#include "transform/Transform.h"

class IShape {
public:
    virtual void draw() = 0;

    virtual void setView(const glm::tmat4x4<float> &mvpMatrix) = 0;

    virtual void setProjection(const glm::tmat4x4<float> &mvpMatrix) = 0;

    virtual Transform & getTransformation() = 0;

};

#endif //NDK_ISHAPE_H
