package com.neocaptainnemo.ndk.graphics;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.glGetString;


public class SampleRenderer implements GLSurfaceView.Renderer {

    private Context context;

    private OpenGlJni openGlJni;

    public SampleRenderer(Context context, OpenGlJni openGlJni) {
        this.context = context;
        this.openGlJni = openGlJni;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        openGlJni.onSurfaceCreated(context.getAssets());
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        openGlJni.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        openGlJni.onDrawFrame();
    }
}
