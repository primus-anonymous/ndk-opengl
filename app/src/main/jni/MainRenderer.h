#ifndef NDK_ENGINE_H
#define NDK_ENGINE_H

#include <GLES2/gl2.h>
#include <camera/Camera.h>
#include <shadow/ShadowMap.h>
#include <opengl/IRenderer.h>
#include <opengl/OpenGlShadowMapRenderer.h>
#include <opengl/OpenGlSceneRenderer.h>
#include <map>

class MainRenderer {
public:

    MainRenderer(AssetsReader &reader);

    void onViewChanged(int w, int h);

    void onRender();

    ~MainRenderer();

    void onSwipedLeft();

    void onSwipedRight();

    void onSwipedBottom();

    void onSwipedTop();

    void onZoomedIn();

    void onZoomedOut();

private:

    glm::tmat4x4<float> sceneProjection;

    glm::tmat4x4<float> shadowMapProjection;

    std::map<std::string, BaseShape *> shapes;

    Light light;

    Camera camera;

    int width;

    int height;

    float cameraStep = 0.3f;

    float lightXStep = 0.f;

    float lightXStepSign = 1.0f;

    ShadowMap *shadowMap = nullptr;

    AssetsReader reader;

    OpenGlSceneRenderer *sceneRenderer;

    OpenGlShadowMapRenderer *shadowMapRenderer;

    const static std::string DICE_1;
    const static std::string DICE_2;
    const static std::string DICE_3;

    const static std::string PLANE;
    const static std::string POINT;
};


#endif //NDK_ENGINE_H
