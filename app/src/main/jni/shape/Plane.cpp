#include "Plane.h"

Plane::Plane(int width, int height) {

    generateVert(width, height);

}

void Plane::generateVert(int width, int height) {

    int halfWidth = width / 2;
    int halfHeight = height / 2;

    for (int j = -halfHeight; j < halfHeight; j++) {
        for (int i = -halfWidth; i < halfWidth; i++) {

            verticies.push_back(i);
            verticies.push_back(0);
            verticies.push_back(j);

            verticies.push_back(i + 1);
            verticies.push_back(0);
            verticies.push_back(j);

            verticies.push_back(i);
            verticies.push_back(0);
            verticies.push_back(j + 1);

            verticies.push_back(i + 1);
            verticies.push_back(0);
            verticies.push_back(j + 1);


            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            normals.push_back(0);
            normals.push_back(1);
            normals.push_back(0);

            uvs.push_back(0.0f);
            uvs.push_back(1.0f);

            uvs.push_back(1.0f);
            uvs.push_back(1.0f);

            uvs.push_back(0.0f);
            uvs.push_back(0.0f);

            uvs.push_back(1.0f);
            uvs.push_back(0.0f);

        }
    }
}
