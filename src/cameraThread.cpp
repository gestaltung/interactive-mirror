//
//  cameraThread.cpp
//  interactiveMirror
//
//  Created by Zac Ioannidis on 3/22/16.


#include "cameraThread.hpp"


void CameraThread::threadedFunction() {
    while (isThreadRunning()) {
        if (lock()) {
             cam.update();
            
            if (cam.isFrameNew()) {
                image.setFromPixels(cam.getPixels());
                image.update();
            }
            
            unlock();
        }
        else {
            ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
        }
    }
}

// Set up the thread.
void CameraThread::setup() {
    image.allocate(1024,768,OF_IMAGE_COLOR);
    image.setUseTexture(false);
    
    cam.setDesiredFrameRate(60);
    cam.initGrabber(1024, 768);
    cam.setUseTexture(false);
}

// Start the thread.
void CameraThread::start() {
    startThread();
}

/// Signal the thread to stop.
void CameraThread::stop() {
    stopThread();
}

// Can only be called from the main thread because it
// includes OpenGL calls.
void CameraThread::drawCamera() {
    if (lock()) {
        cam.draw(0,0);
        unlock();
    }
    else {
        ofLogWarning("drawCamera()") << "Unable to lock mutex.";
    }
    
}