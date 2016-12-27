#include <jni.h>
#include "Main.h"


extern "C" {


Main *mainRenderer;


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
    mainRenderer = new Main(reader);
}


JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeLeft(JNIEnv *env, jobject instance) {

    mainRenderer->onSwipedLeft();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeRight(JNIEnv *env, jobject instance) {

    mainRenderer->onSwipedRight();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeBottom(JNIEnv *env, jobject instance) {

    mainRenderer->onSwipedBottom();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onSwipeTop(JNIEnv *env, jobject instance) {

    mainRenderer->onSwipedTop();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onZoomIn(JNIEnv *env, jobject instance) {

    mainRenderer->onZoomedIn();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_onZoomOut(JNIEnv *env, jobject instance) {

    mainRenderer->onZoomedOut();
}

JNIEXPORT void JNICALL
Java_com_neocaptainnemo_ndk_graphics_OpenGlJni_recycle(JNIEnv *env, jobject instance) {
    delete mainRenderer;
}

}