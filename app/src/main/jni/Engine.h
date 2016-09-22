#ifndef NDK_ENGINE_H
#define NDK_ENGINE_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLES2/gl2.h>
#include <shape/IShape.h>
#include <android/asset_manager.h>
#include <camera/Camera.h>
#include "shader/Program.h"

class Engine {
public:

    Engine();

    void onViewChanged(int w, int h);

    void onDraw();

    ~Engine();

    void addShape(IShape *shape);

    Camera & getCamera();

private:

    glm::tmat4x4<float> projection;

    std::vector<IShape *> shapes;

    Camera camera;
};


#endif //NDK_ENGINE_H
