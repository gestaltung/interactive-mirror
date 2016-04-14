//
//  cameraThread.hpp
//  interactiveMirror
//
//  Created by Zac Ioannidis on 3/22/16.
//
//  This class is responsible for grabbing webcam video and tracking faces.
//  Runs on a separate thread.

#ifndef cameraThread_hpp
#define cameraThread_hpp

#include "ofThread.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"

using namespace ofxCv;
using namespace cv;

class CameraThread : public ofThread {
    public:
    void threadedFunction();
    void start();
    void stop();
    void drawCamera();
    ofTexture getCameraTexture();
    
    ofTexture camTex;
    
    protected:
    // Camera and face tracking
    ofVideoGrabber cam;
    ofPixels vidPixels;
    ofxFaceTracker tracker;

};

#endif /* cameraThread_hpp */
