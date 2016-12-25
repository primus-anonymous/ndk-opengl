#ifndef NDK_OPENGL_OPENGLSHADOWMAPRENDERER_H
#define NDK_OPENGL_OPENGLSHADOWMAPRENDERER_H


#include <glm/detail/type_mat4x4.hpp>
#include <shader/Program.h>
#include <texture/AssetsReader.h>
#include <light/Light.h>
#include <shadow/ShadowMap.h>
#include "IRenderer.h"

class OpenGlShadowMapRenderer : public IRenderer {
public:
    OpenGlShadowMapRenderer(AssetsReader &reader);

    virtual ~OpenGlShadowMapRenderer();

    void setProjection(const glm::tmat4x4<float> &projection);

    void setLight(const Light &l);

    virtual void render(Polygon &polygon) override;

    virtual void render(Plane &plane) override;

    virtual void render(Point &point) override;

    glm::tmat4x4<float> getProjectionView();

private:

    Program *program;
    Light light;

    glm::tmat4x4<float> projection;
    glm::tmat4x4<float> shadowMapView;

    void renderBaseShape(BaseShape &shape, GLenum type, int count) const;
};


#endif //NDK_OPENGL_OPENGLSHADOWMAPRENDERER_H
