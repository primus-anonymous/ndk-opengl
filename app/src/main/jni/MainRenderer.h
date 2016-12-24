#ifndef NDK_ENGINE_H
#define NDK_ENGINE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLES2/gl2.h>
#include <android/asset_manager.h>
#include <camera/Camera.h>
#include <shadow/ShadowMap.h>
#include <opengl/IRenderer.h>
#include <opengl/OpenGlShadowMapRenderer.h>
#include "shader/Program.h"
#include <map>

class MainRenderer {
public:

    MainRenderer(AssetsReader &reader);

    void onViewChanged(int w, int h);

    void onRender();

    ~MainRenderer();

    Camera &getCamera();

private:

    glm::tmat4x4<float> sceneProjection;

    glm::tmat4x4<float> shadowMapProjection;

    std::map<std::string, BaseShape *> shapes;

    Light pointLight;

    std::vector<Texture *> buildDiceTextures();

    void setTextures(Polygon *cube, const std::vector<Texture *> textures);

    Camera camera;

    int width;

    int height;

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
