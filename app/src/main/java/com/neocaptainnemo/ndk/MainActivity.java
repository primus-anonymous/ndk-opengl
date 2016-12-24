package com.neocaptainnemo.ndk;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;

import com.neocaptainnemo.ndk.graphics.OpenGlJni;
import com.neocaptainnemo.ndk.graphics.SampleRenderer;

public class MainActivity extends AppCompatActivity implements View.OnTouchListener {

    private SampleSurfaceView surfaceView;
    private OpenGlJni openGlJni = new OpenGlJni();

    private ScaleGestureDetector scaleGestureDetector;
    private OnSwipeTouchListener swipeGestureDetector;
    private boolean scaleDetected;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        swipeGestureDetector = new OnSwipeTouchListener(this);
        scaleGestureDetector = new ScaleGestureDetector(this, new ScaleGestureDetector.OnScaleGestureListener() {
            @Override
            public boolean onScale(ScaleGestureDetector detector) {
                float factor = detector.getScaleFactor();

                if (factor > 1.0) {
                    openGlJni.onZoomIn();
                }

                if (factor < 1.0) {
                    openGlJni.onZoomOut();
                }

                return true;
            }

            @Override
            public boolean onScaleBegin(ScaleGestureDetector detector) {
                scaleDetected = true;
                return true;
            }

            @Override
            public void onScaleEnd(ScaleGestureDetector detector) {
                scaleDetected = false;
            }
        });

        surfaceView = new SampleSurfaceView(this);
        surfaceView.setOnTouchListener(this);
        setContentView(surfaceView);
    }


    @Override
    protected void onResume() {
        super.onResume();
        surfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        surfaceView.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        surfaceView.onDestroy();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        scaleGestureDetector.onTouchEvent(event);
        swipeGestureDetector.onTouch(v, event);
        return true;
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);
        if (hasFocus) {
            getWindow().getDecorView().setSystemUiVisibility(
                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                            | View.SYSTEM_UI_FLAG_FULLSCREEN
                            | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        }
    }

    public class OnSwipeTouchListener implements View.OnTouchListener {

        private final GestureDetector gestureDetector;

        OnSwipeTouchListener(Context ctx) {
            gestureDetector = new GestureDetector(ctx, new GestureListener());
        }

        @Override
        public boolean onTouch(View v, MotionEvent event) {
            return gestureDetector.onTouchEvent(event);
        }

        void onSwipeRight() {
            openGlJni.onSwipeRight();
        }

        void onSwipeLeft() {
            openGlJni.onSwipeLeft();
        }

        void onSwipeTop() {
            openGlJni.onSwipeTop();
        }

        void onSwipeBottom() {
            openGlJni.onSwipeBottom();
        }

        private final class GestureListener extends GestureDetector.SimpleOnGestureListener {

            private static final int SWIPE_THRESHOLD = 100;
            private static final int SWIPE_VELOCITY_THRESHOLD = 100;

            @Override
            public boolean onDown(MotionEvent e) {
                return true;
            }

            @Override
            public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
                if (scaleDetected) {
                    return false;
                }
                boolean result = false;
                try {
                    float diffY = e2.getY() - e1.getY();
                    float diffX = e2.getX() - e1.getX();
                    if (Math.abs(diffX) > Math.abs(diffY)) {
                        if (Math.abs(diffX) > SWIPE_THRESHOLD) {
                            if (diffX > 0) {
                                onSwipeRight();
                            } else {
                                onSwipeLeft();
                            }
                        }
                        result = true;
                    } else if (Math.abs(diffY) > SWIPE_THRESHOLD) {
                        if (diffY > 0) {
                            onSwipeBottom();
                        } else {
                            onSwipeTop();
                        }
                    }
                    result = true;

                } catch (Exception exception) {
                    exception.printStackTrace();
                }
                return result;
            }

        }
    }

    class SampleSurfaceView extends GLSurfaceView {


        public SampleSurfaceView(Context context) {
            super(context);
            setEGLContextClientVersion(2);
            setRenderer(new SampleRenderer(context, openGlJni));
        }

        public void onDestroy() {
            openGlJni.recycle();
        }
    }
}
