//
//  cameraThread.cpp
//  interactiveMirror
//
//  Created by Zac Ioannidis on 3/22/16.


#include "cameraThread.hpp"


void CameraThread::threadedFunction() {
    while (isThreadRunning()) {
    //        lock();
    
        //  Try to lock thread
        if (lock()) {
            // cam.update();
            
            // or this
            if (cam.isFrameNew()) {
                cam.update();
                
                ofPixels &pixels = cam.getPixels();
                for(int i = 0; i < pixels.size(); i++) {
                    vidPixels[i] = pixels[i];
                }
                camTex.loadData(vidPixels);
            }
            
//            drawCamera();

            unlock();
            
            // 60 fps
            // sleep(1000/60);
        }
        else {
            // If we reach this else statement, it means that we could not
            // lock our mutex, and so we do not need to call unlock().
            // Calling unlock without locking will lead to problems.
            ofLogWarning("threadedFunction()") << "Unable to lock mutex.";
        }

    //        if(cam.isFrameNew()) {
    //            tracker.update(toCv(cam));
    //        }
    //        unlock();
    }
}

/// Start the thread.
void CameraThread::start() {
    vidPixels.allocate(1024,768,OF_PIXELS_RGB);
    camTex.allocate(vidPixels);
//    cam.initGrabber(1024, 768, false);
    cam.initGrabber(1024, 768);
    cam.setUseTexture(true);
//    tracker.setup();
    // Mutex blocking is set to true by default
    // It is rare that one would want to use startThread(false).
    startThread();
}

/// Signal the thread to stop.  After calling this method,
/// isThreadRunning() will return false and the while loop will stop
/// next time it has the chance to.
void CameraThread::stop() {
    stopThread();
}

ofTexture CameraThread::getCameraTexture() {
    if (lock()) {
        ofTexture tex = cam.getTexture();
//        cam.getTexture();
        unlock();
        return tex;
    }
    else {
        ofLogWarning("getCameraTexture()") << "Unable to lock mutex.";
    }
    
}

// Can only be called from the main thread because it
// includes OpenGL calls.
void CameraThread::drawCamera() {
    if (lock()) {
//        stringstream ss;
//        ss << "I am a slowly increasing thread. " << endl;
//        ss << "My current count is: ";
//        ofDrawBitmapString(ss.str(), 50, 56);
//    camTex.draw(0,0);
    cam.draw(0,0);

        unlock();
    }
    else {
        ofLogWarning("drawCamera()") << "Unable to lock mutex.";
    }
    
}