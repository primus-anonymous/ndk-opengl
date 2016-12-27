#include <meshes.h>
#include "Polygon.h"

Polygon::Polygon(const std::vector<float> &ver,
                 const std::vector<float> &norm, const std::vector<float> &textCoords, int toDraw)
        : BaseShape("polygon"), toDraw(toDraw) {
    verticies = ver;
    normals = norm;
    uvs = textCoords;
}

Polygon::~Polygon() {

}


int Polygon::getToDraw() {
    return toDraw;
}

Polygon *Polygon::cubeInstance() {
    return new Polygon(QUBE, NORMALS, TEXTURE_COORDS, 36);
}





