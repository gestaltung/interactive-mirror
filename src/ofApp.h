#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxJSON.h"
#include "controller.hpp"
#include "cameraThread.hpp"

using namespace ofxCv;
using namespace cv;

#define DISPLAY_MODE 0;
#define PASSIVE_MODE 1;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int WIDTH, HEIGHT;
    
        ofShader shader;
        ofImage noiseTex;
        ofFbo fbo;
    
        // Threaded FaceTracker specific
        ofxFaceTrackerThreaded tracker;
        ofVec2f position;
        float scale;
        ofVec3f orientation;
        ofMatrix4x4 rotationMatrix;
        Mat translation, rotation;
        ofMatrix4x4 pose;
        
        ofEasyCam easyCam;
        ofTrueTypeFont font;
    
        // JSON requests
        GSTController controller;
    
        // Camera and face tracking
        CameraThread cameraThread;
        ofTexture videoTexture;
};
