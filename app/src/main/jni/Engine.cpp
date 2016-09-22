#include "Engine.h"

Engine::Engine() {

    glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void Engine::onViewChanged(int width, int height) {
    glViewport(0, 0, width, height);

    float ratio = (float) width / height;

    projection = glm::frustum(-ratio, ratio, -1.f, 1.f, 2.f, 24.f);

}

void Engine::onDraw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (IShape *in : shapes) {
        in->setView(camera.getMatrix());
        in->setProjection(projection);
        in->draw();
    }
}

Engine::~Engine() {

    for (IShape *in : shapes) {
        delete in;
    }
}


void Engine::addShape(IShape *shape) {
    shapes.push_back(shape);
}

Camera &Engine::getCamera() {
    return camera;
}
