#include <meshes.h>
#include "Cube.h"

Cube::Cube(AssetsReader &reader)  : Polygon(reader, QUBE, NORMALS, TEXTURE_COORDS, 36) {

}
