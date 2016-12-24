#include <jni.h>
#include <shape/Polygon.h>
#include <shape/Point.h>
#include <shape/Plane.h>
#include <opengl/OpenGlSceneRenderer.h>
#include "MainRenderer.h"


extern "C" {


MainRenderer *mainRenderer;


float step = 0.3f;

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSurfaceChanged(JNIEnv *env, jobject instance,
                                                                jint width, jint height) {
    mainRenderer->onViewChanged(width, height);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onDrawFrame(JNIEnv *env, jobject instance) {
    mainRenderer->onRender();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSurfaceCreated(JNIEnv *env, jobject instance,
                                                                jobject assets) {

    AAssetManager *mgr = AAssetManager_fromJava(env, assets);

    AssetsReader reader(mgr);
    mainRenderer = new MainRenderer(reader);
}


JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeLeft(JNIEnv *env, jobject instance) {
    mainRenderer->getCamera().setViewAtX(mainRenderer->getCamera().getViewAtX() + step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeRight(JNIEnv *env, jobject instance) {
    mainRenderer->getCamera().setViewAtX(mainRenderer->getCamera().getViewAtX() - step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeBottom(JNIEnv *env, jobject instance) {
    mainRenderer->getCamera().setViewAtY(mainRenderer->getCamera().getViewAtY() + step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeTop(JNIEnv *env, jobject instance) {
    mainRenderer->getCamera().setViewAtY(mainRenderer->getCamera().getViewAtY() - step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onZoomIn(JNIEnv *env, jobject instance) {
    mainRenderer->getCamera().setViewAtZ(mainRenderer->getCamera().getViewAtZ() - step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onZoomOut(JNIEnv *env, jobject instance) {
    mainRenderer->getCamera().setViewAtZ(mainRenderer->getCamera().getViewAtZ() + step);
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_recycle(JNIEnv *env, jobject instance) {
    delete mainRenderer;
}

}