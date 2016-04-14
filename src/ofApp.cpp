#include "ofApp.h"

using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    //    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
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
    
    //    ofEnableNormalizedTexCoords();
    //    ofSetOrientation(OF_ORIENTATION_DEFAULT,false);
    ofDisableArbTex();
    
    
    // start the controller thread
    controller.start();
    
    // Start the camera thread
    cameraThread.start();
    
    noiseTex.load("noiseTex.png");
    
    font.load("futura.ttf", 24);


    //    cam.initGrabber(1024, 768);
    shader.load("distortion.vert", "distortion.frag");
    //    tracker.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
//    cameraThread.cam.update();
    
    // Lock access to the incoming camera resource
//    controller.lock();
    
    // Release access to camera resource
//    controller.unlock();
//    if(controller.cam.isFrameNew()) {
//        if (ofGetFrameNum() % 60 == 0) {
//            controller.tracker.update(toCv(controller.cam));
//        }
//    }
    
    fbo.begin();
//    cam.draw(0, 0);

//    cameraThread.drawCamera();
    ofFill();
    ofSetColor(0, 255, 0);
    ofDrawRectangle(0,0,400,400);

    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    //    shader.setUniformTexture("srcTex", cameraThread.getCameraTexture(), 1);
    //    shader.setUniformTexture("noiseTex", noiseTex.getTexture(), 1);
    //    shader.setUniform2f("u_resolution", WIDTH, HEIGHT);
    //    shader.setUniform1f("u_time", ofGetElapsedTimef());


    shader.end();
//    fbo.draw(0,0);
    controller.drawMetrics(WIDTH, HEIGHT);
    
    
//    if(tracker.getFound()) {
//        cam.draw(0, 0);
//        ofSetLineWidth(1);
//        tracker.draw();
//    }

}

//--------------------------------------------------------------
void ofApp::drawMetrics(){
    ofColor(255, 255, 255);
    
    font.drawString(controller.currentDate.substr(0,4), 20, HEIGHT-80);
    font.drawString("/" + controller.currentDate.substr(4,2), 130, HEIGHT-80);
    font.drawString("/" + controller.currentDate.substr(6,2), 205, HEIGHT-80);
    font.drawString(ofToString(controller.overallDistance) + " KM", 20, HEIGHT-40);
    font.drawString(ofToString(controller.totalSteps) + " STEPS", 20, HEIGHT-10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='l') {
        shader.load("distortion.vert", "distortion.frag");
    }
    
    if (key==OF_KEY_LEFT) {
        controller.setDate("20160314");
        controller.getMetricsForDay();
        
        // If you don't want to do multithreaded, uncomment below
        // controller.setAggregateData();
    }
    
    if (key==OF_KEY_RIGHT) {
        controller.setDate("20160315");
        controller.getMetricsForDay();
        
        // If you don't want to do multithreaded, uncomment below
        // controller.setAggregateData();
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    cameraThread.stopThread();
//    controller.stopThread();
    controller.stop();
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
