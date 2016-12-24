#include "BaseShape.h"

#ifndef NDK_PLANE_H
#define NDK_PLANE_H

class Plane : public BaseShape {

public:
    Plane(int width, int height);


private:
    void generateVert(int width, int height);
};

#endif //NDK_PLANE_H
