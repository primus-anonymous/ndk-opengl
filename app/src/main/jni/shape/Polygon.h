#ifndef NDK_POLYGON_H
#define NDK_POLYGON_H

#include "IShape.h"
#include "BaseShape.h"
#include <vector>
#include <glm/detail/type_mat4x4.hpp>
#include <shader/Program.h>
#include <texture/Texture.h>
#include <texture/AssetsReader.h>

class Polygon : public BaseShape {

public:

    virtual ~Polygon();

    virtual void draw() override;

    Polygon(AssetsReader & reader, const std::vector<float> & ver, const std::vector<float> & norm,
            const std::vector<float> & textCoords, int toDraw);

private:
    int toDraw;
};


#endif //NDK_POLYGON_H
