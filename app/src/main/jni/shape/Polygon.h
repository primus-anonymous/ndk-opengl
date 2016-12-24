#ifndef NDK_POLYGON_H
#define NDK_POLYGON_H

#include "BaseShape.h"
#include <vector>

class Polygon : public BaseShape {

public:

    virtual ~Polygon();

    Polygon(const std::vector<float> &ver, const std::vector<float> &norm,
            const std::vector<float> &textCoords, int toDraw);

    int getToDraw();

    static Polygon* cubeInstance();

private:
    int toDraw;
};


#endif //NDK_POLYGON_H
