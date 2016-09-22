#include "BaseShape.h"

#ifndef NDK_POINT_H
#define NDK_POINT_H

class Point : public BaseShape {

public:
    virtual ~Point();

    virtual void draw() override;

    Point(AssetsReader &reader);
};

#endif //NDK_POINT_H
