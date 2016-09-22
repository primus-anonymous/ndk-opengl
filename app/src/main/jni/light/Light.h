#ifndef NDK_LIGHT_H
#define NDK_LIGHT_H

#include <transform/Transform.h>

class Light {
public:

    void setAmbientComponent(float amb);

    float getAmbientComponent();

    void setX(float x);

    float getX();

    void setY(float y);

    float getY();

    void setZ(float z);

    float getZ();

    void setSpecularExp(float exp);

    float  getSpecularExp();

private:
    float ambient = 0.0;
    float specularExp = 0.0;

    float xPos = 0.0f;
    float yPos = 0.0;
    float zPos = 0.0;
};
#endif //NDK_LIGHT_H
