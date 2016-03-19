#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    
    WIDTH = ofGetScreenWidth();
    WIDTH = 1024;
    HEIGHT = ofGetScreenHeight();
    HEIGHT = 768;
    
    fbo.allocate(WIDTH, HEIGHT);
    fbo.begin();
    ofClear(255,255,255, 0);
    fbo.end();
    
    ofEnableNormalizedTexCoords();
    ofSetOrientation(OF_ORIENTATION_DEFAULT,false);
    ofDisableArbTex();
    
    controller.setAccessTokens();
    cout << controller.movesAccessToken;
    
    noiseTex.load("noiseTex.png");
    
    cam.initGrabber(1024, 768);
    
    shader.load("distortion.vert", "distortion.frag");
    
    tracker.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cam.update();
//    if(cam.isFrameNew()) {
//        if (ofGetFrameNum() % 60 == 0) {
//            tracker.update(toCv(cam));
//        }
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniformTexture("srcTex", cam.getTexture(), 1);
    shader.setUniformTexture("noiseTex", noiseTex.getTexture(), 2);
    shader.setUniform2f("u_resolution", WIDTH, HEIGHT);
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    fbo.begin();
    cam.draw(0, 0);
    fbo.end();
    fbo.draw(0,0);
    shader.end();
    

    if(tracker.getFound()) {
//        cam.draw(0, 0);
        ofSetLineWidth(1);
        tracker.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='l') {
        shader.load("distortion.vert", "distortion.frag");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
