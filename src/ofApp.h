#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "ofxJSON.h"
#include "controller.hpp"

using namespace ofxCv;
using namespace cv;

#define DISPLAY_MODE 0;
#define PASSIVE_MODE 1;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    
        ofVideoGrabber cam;
        ofVideoGrabber cam2;
        ofxFaceTracker tracker;
        ofVec2f position;
        float scale;
        ofVec3f orientation;
        ofMatrix4x4 rotationMatrix;
    
        int WIDTH, HEIGHT;
    
        ofShader shader;
        ofImage noiseTex;
        ofFbo fbo;
    
        Mat translation, rotation;
        ofMatrix4x4 pose;
        
        ofEasyCam easyCam;
    
        // JSON requests
        GSTController controller;
//    std::string userId = "56b8dee9dc6b20e576447b91";
//    ofxJSONElement json;
//    std::string movesAccessToken;
		
};
