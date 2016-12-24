package com.neocaptainnemo.ndk.graphics;

import android.content.res.AssetManager;

public class OpenGlJni {

    static {
        System.loadLibrary("jni");
    }


    public native void onSurfaceChanged(int width, int height);

    public native void onDrawFrame();

    public native void onSurfaceCreated(AssetManager manager);

    public native void onSwipeLeft();

    public native void onSwipeRight();

    public native void onSwipeBottom();

    public native void onZoomIn();

    public native void onZoomOut();

    public native void onSwipeTop();

    public native void recycle();
}
