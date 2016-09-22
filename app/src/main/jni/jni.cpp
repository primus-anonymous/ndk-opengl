#include <jni.h>
#include <shape/Polygon.h>
#include <shape/Cube.h>
#include <shape/Point.h>
#include <shape/Plane.h>
#include "Engine.h"


extern "C" {


Engine *engine;
Polygon *dice1, *dice2, *dice3;
Plane *plane;
Point * point;

float step = 0.3f;

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSurfaceChanged(JNIEnv *env, jobject instance,
                                                                jint width, jint height) {
    engine->onViewChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onDrawFrame(JNIEnv *env, jobject instance) {

    float rotation = dice1->getTransformation().getRotationY() + 0.020f;
    if (rotation > 360.f) {
        rotation = 0.f;
    }
    dice1->getTransformation().builder().rotationY(rotation).buildAsSRT();

    rotation = dice2->getTransformation().getRotationZ() + 0.020f;
    if (rotation > 360.f) {
        rotation = 0.f;
    }

    dice2->getTransformation().builder().rotationZ(rotation).buildAsSRT();

    rotation = dice3->getTransformation().getRotationX() + 0.020f;
    if (rotation > 360.f) {
        rotation = 0.f;
    }

    dice3->getTransformation().builder().rotationX(rotation).buildAsSRT();

    engine->onDraw();
}


void setTextures(Polygon *cube, const std::vector<Texture *> textures) {
    for (auto texture : textures) {
        cube->addTexture(texture);
    }
}

std::vector<Texture *> buildDiceTextures(AssetsReader &reader) {
    std::vector<Texture *> diceTextures;

    Texture *texture1 = new Texture();
    texture1->bind(reader.readPng("dice1.png"));
    diceTextures.push_back(texture1);

    Texture *texture2 = new Texture();
    texture2->bind(reader.readPng("dice2.png"));
    diceTextures.push_back(texture2);

    Texture *texture3 = new Texture();
    texture3->bind(reader.readPng("dice3.png"));
    diceTextures.push_back(texture3);

    Texture *texture4 = new Texture();
    texture4->bind(reader.readPng("dice4.png"));
    diceTextures.push_back(texture4);

    Texture *texture5 = new Texture();
    texture5->bind(reader.readPng("dice5.png"));
    diceTextures.push_back(texture5);

    Texture *texture6 = new Texture();
    texture6->bind(reader.readPng("dice6.png"));
    diceTextures.push_back(texture6);
    return diceTextures;
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSurfaceCreated(JNIEnv *env, jobject instance,
                                                                jobject assets) {
    engine = new Engine();
    AAssetManager *mgr = AAssetManager_fromJava(env, assets);

    AssetsReader reader(mgr);
    Light pointLight;
    pointLight.setAmbientComponent(0.2f);
    pointLight.setSpecularExp(1.5f);
    pointLight.setX(4.0f);
    pointLight.setY(3.0f);
    pointLight.setZ(2.0f);

    dice1 = new Cube(reader);
    dice1->setLight(pointLight);

    dice2 = new Cube(reader);
    dice2->setLight(pointLight);
    dice2->getTransformation().builder()
            .translationX(-2.f).translationY(2.f).translationZ(1.0f).buildAsSRT();

    dice3 = new Cube(reader);
    dice3->setLight(pointLight);
    dice3->getTransformation().builder()
            .translationX(2.f).translationY(-2.f).translationZ(-1.0f).buildAsSRT();


    auto diceTextures = buildDiceTextures(reader);

    setTextures(dice1, diceTextures);
    setTextures(dice2, diceTextures);
    setTextures(dice3, diceTextures);

    point = new Point(reader);
    point->getTransformation().builder().translationX(pointLight.getX()).translationY(pointLight.getY())
            .translationZ(pointLight.getZ()).buildAsSRT();

    plane = new Plane(reader, 24, 24);
    plane->getTransformation().builder().translationY(-3.0f).buildAsSRT();

    Texture *table = new Texture();
    table->bind(reader.readPng("poker_table.png"));
    plane->addTexture(table);

    engine->addShape(dice1);
    engine->addShape(dice2);
    engine->addShape(dice3);
    engine->addShape(point);
    engine->addShape(plane);
}


JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeLeft(JNIEnv *env, jobject instance) {
    engine->getCamera().setViewAtX(engine->getCamera().getViewAtX() + step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeRight(JNIEnv *env, jobject instance) {
    engine->getCamera().setViewAtX(engine->getCamera().getViewAtX() - step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeBottom(JNIEnv *env, jobject instance) {
    engine->getCamera().setViewAtY(engine->getCamera().getViewAtY() + step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeTop(JNIEnv *env, jobject instance) {
    engine->getCamera().setViewAtY(engine->getCamera().getViewAtY() - step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onZoomIn(JNIEnv *env, jobject instance) {
    engine->getCamera().setViewAtZ(engine->getCamera().getViewAtZ() - step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onZoomOut(JNIEnv *env, jobject instance) {
    engine->getCamera().setViewAtZ(engine->getCamera().getViewAtZ() + step);
}

}