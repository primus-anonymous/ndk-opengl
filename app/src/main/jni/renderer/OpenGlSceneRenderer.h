#ifndef NDK_OPENGL_OPENGLRENDERER_H
#define NDK_OPENGL_OPENGLRENDERER_H


#include <texture/AssetsReader.h>
#include <light/Light.h>
#include <shader/Program.h>
#include <shadow/ShadowMap.h>
#include "IRenderer.h"

class OpenGlSceneRenderer : public IRenderer {

public:

    OpenGlSceneRenderer(AssetsReader &assetsRe);

    virtual void render(Polygon &polygon) override;

    virtual void render(Plane &plane) override;

    virtual void render(Point &point) override;

    void setView(const glm::tmat4x4<float> &view);

    void setProjection(const glm::tmat4x4<float> &projection);

    void setLight(const Light &l);

    void setShadowMap(ShadowMap * shadowMap);

    void setShadowMapProjectionView(const glm::tmat4x4<float> &shadowMapMVp);

    virtual ~OpenGlSceneRenderer();

private:
    AssetsReader assetsReader;

    glm::tmat4x4<float> view;
    glm::tmat4x4<float> projection;
    glm::tmat4x4<float> shadowMapMvp;
    Light light;

    Program *polygonProgram = nullptr;
    Program *pointProgram = nullptr;

    ShadowMap * shadowMap;

    Program *getPolygonProgram();

    Program *getPointProgram();

    static const glm::tmat4x4<float> BIAS;

};


#endif //NDK_OPENGL_OPENGLRENDERER_H
