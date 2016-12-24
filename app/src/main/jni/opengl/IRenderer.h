#ifndef NDK_OPENGL_IRENDERER_H
#define NDK_OPENGL_IRENDERER_H

#include <shape/Polygon.h>
#include <shape/Plane.h>
#include <shape/Point.h>

class IRenderer {

    virtual void render(Polygon &polygon) = 0;

    virtual void render(Plane &plane) = 0;

    virtual void render(Point &point) = 0;

};

#endif //NDK_OPENGL_IRENDERER_H
