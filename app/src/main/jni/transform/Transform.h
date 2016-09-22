#ifndef NDK_TRANSFORM_H
#define NDK_TRANSFORM_H

#include <glm/detail/type_mat4x4.hpp>
#include "transform/Transform.h"

class Transform {

public:

    class Builder {

    public :
        Builder &translationX(float x);

        Builder &translationY(float y);

        Builder &translationZ(float z);

        Builder &rotationX(float x);

        Builder &rotationY(float y);

        Builder &rotationZ(float z);

        Builder &scaleX(float x);

        Builder &scaleY(float y);

        Builder &scaleZ(float z);

        void buildAsSRT();

        void buildAsTRS();

        void buildAsTSR();

        Builder(Transform &transform);

    private:
        Transform &outer;
    };

    float getTranslationX();

    float getTranslationY();

    float getTranslationZ();

    float getRotationX();

    float getRotationY();

    float getRotationZ();

    float getScaleX();

    float getScaleY();

    float getScaleZ();

    Builder &builder();

    Transform();

    virtual ~Transform();

    glm::tmat4x4<float> modelMatrix();


private:

    float translationX = 0.f;
    float translationY = 0.f;
    float translationZ = 0.f;

    float angleX = 0.f;
    float angleY = 0.f;
    float angleZ = 0.f;

    float scaleX = 1.f;
    float scaleY = 1.f;
    float scaleZ = 1.f;

    glm::tmat4x4<float> model;

    Builder builderInstance;
};

#endif //NDK_TRANSFORM_H
