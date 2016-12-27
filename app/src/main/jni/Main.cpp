#include "Main.h"

const std::string Main::DICE_1 = "DICE_1";
const std::string Main::DICE_2 = "DICE_2";
const std::string Main::DICE_3 = "DICE_3";

const std::string Main::PLANE = "PLANE";
const std::string Main::POINT = "POINT";

Main::Main(AssetsReader &read) : reader(read) {

    glEnable(GL_DEPTH_TEST);

    sceneRenderer = new OpenGlSceneRenderer(reader);
    shadowMapRenderer = new OpenGlShadowMapRenderer(reader);

    light.setAmbientComponent(0.2f);
    light.setSpecularExp(1.5f);
    light.setY(9.0f);
    light.setZ(.0f);

    Polygon *dice1 = Polygon::cubeInstance();

    Polygon *dice2 = Polygon::cubeInstance();
    dice2->getTransformation().builder()
            .translationX(-2.f).translationY(2.f).translationZ(1.0f).buildAsSRT();

    Polygon *dice3 = Polygon::cubeInstance();
    dice3->getTransformation().builder()
            .translationX(2.f).translationY(-2.f).translationZ(-1.0f).buildAsSRT();

    std::vector<Texture *> diceTextures;

    diceTextures.push_back(Texture::instance(reader.readPng("dice1.png")));
    diceTextures.push_back(Texture::instance(reader.readPng("dice2.png")));
    diceTextures.push_back(Texture::instance(reader.readPng("dice3.png")));
    diceTextures.push_back(Texture::instance(reader.readPng("dice4.png")));
    diceTextures.push_back(Texture::instance(reader.readPng("dice5.png")));
    diceTextures.push_back(Texture::instance(reader.readPng("dice6.png")));

    dice1->addTexture(diceTextures);
    dice2->addTexture(diceTextures);
    dice3->addTexture(diceTextures);

    Plane *plane = new Plane(18, 10);
    plane->getTransformation().builder().translationY(-3.0f).buildAsSRT();

    plane->addTexture(Texture::instance(reader.readPng("poker_table.png")));

    shapes[DICE_1] = dice1;
    shapes[DICE_2] = dice2;
    shapes[DICE_3] = dice3;
    shapes[PLANE] = plane;

    shapes[POINT] = new Point();

    camera.setViewAtY(6.f);
}


void Main::onViewChanged(int width, int height) {

    this->width = width;
    this->height = height;

    float ratio = (float) width / height;
    sceneProjection = glm::frustum(-ratio, ratio, -1.f, 1.f, 2.f, 24.f);

    float coefficient = 1.1f;
    shadowMapProjection = glm::frustum(-coefficient * ratio, coefficient * ratio,
                                       -coefficient * 1.f, coefficient * 1.f, 1.f, 100.f);

    shadowMap = new ShadowMap(width, height);
}

void Main::onRender() {

    float rotation = shapes[DICE_1]->getTransformation().getRotationY() + 0.020f;
    if (rotation > 360.f) {
        rotation = 0.f;
    }
    shapes[DICE_1]->getTransformation().builder().rotationY(rotation).buildAsSRT();

    rotation = shapes[DICE_2]->getTransformation().getRotationZ() + 0.020f;
    if (rotation > 360.f) {
        rotation = 0.f;
    }

    shapes[DICE_2]->getTransformation().builder().rotationZ(rotation).buildAsSRT();

    rotation = shapes[DICE_3]->getTransformation().getRotationX() + 0.020f;
    if (rotation > 360.f) {
        rotation = 0.f;
    }

    shapes[DICE_3]->getTransformation().builder().rotationX(rotation).buildAsSRT();

    lightXStep += lightXStepSign * 0.02f;

    if (lightXStep > 2.0f) {
        lightXStepSign = -1.0f;
    }

    if (lightXStep < -4.0f) {
        lightXStepSign = 1.0f;
    }

    light.setX(lightXStep);
    sceneRenderer->setLight(light);
    shadowMapRenderer->setLight(light);
    shapes[POINT]->getTransformation().builder().translationX(light.getX()).translationY(
                    light.getY())
            .translationZ(light.getZ()).buildAsSRT();

    glCullFace(GL_FRONT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap->getFbo());

    glViewport(0, 0, shadowMap->getWidth(), shadowMap->getHeight());

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    shadowMapRenderer->setProjection(shadowMapProjection);

    for (auto iterator = shapes.begin(); iterator != shapes.end(); iterator++) {

        if (Polygon *poly = dynamic_cast<Polygon *>(iterator->second)) {
            shadowMapRenderer->render(*poly);
        }

        if (Plane *plane = dynamic_cast<Plane *>(iterator->second)) {
            shadowMapRenderer->render(*plane);
        }

        if (Point *point = dynamic_cast<Point *>(iterator->second)) {
            shadowMapRenderer->render(*point);
        }
    }

    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCullFace(GL_BACK);
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sceneRenderer->setProjection(sceneProjection);
    sceneRenderer->setView(camera.getMatrix());
    sceneRenderer->setShadowMap(shadowMap);
    sceneRenderer->setShadowMapProjectionView(shadowMapRenderer->getProjectionView());

    for (auto iterator = shapes.begin(); iterator != shapes.end(); iterator++) {

        if (Polygon *poly = dynamic_cast<Polygon *>(iterator->second)) {
            sceneRenderer->render(*poly);
        }

        if (Plane *plane = dynamic_cast<Plane *>(iterator->second)) {
            sceneRenderer->render(*plane);
        }

        if (Point *point = dynamic_cast<Point *>(iterator->second)) {
            sceneRenderer->render(*point);
        }
    }
}

Main::~Main() {

    for (auto iterator = shapes.begin(); iterator != shapes.end(); iterator++) {
        delete iterator->second;
    }

    shapes.clear();

    delete shadowMap;
    delete sceneRenderer;
    delete shadowMapRenderer;
}

void Main::onSwipedLeft() {
    camera.setViewAtX(camera.getViewAtX() + cameraStep);
}

void Main::onSwipedRight() {
    camera.setViewAtX(camera.getViewAtX() - cameraStep);
}

void Main::onSwipedBottom() {
    camera.setViewAtY(camera.getViewAtY() + cameraStep);
}

void Main::onSwipedTop() {
    camera.setViewAtY(camera.getViewAtY() - cameraStep);
}

void Main::onZoomedIn() {
    camera.setViewAtZ(camera.getViewAtZ() - cameraStep);
}

void Main::onZoomedOut() {
    camera.setViewAtZ(camera.getViewAtZ() + cameraStep);
}























