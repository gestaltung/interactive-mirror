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
    //    ofSetOrientation(OF_ORIENTATION_DEFAULT,false);
    ofDisableArbTex();
    
    
    // start the controller thread
    controller.start();
    
    // Setup face tracking
    tracker.setup();
    
    // Start the camera thread
    videoTexture.allocate(1024,768,GL_RGB);
    cameraThread.setup();
    cameraThread.start();
    
    noiseTex.load("noiseTex.png");
    shader.load("distortion.vert", "distortion.frag");
    
    font.load("futura.ttf", 24);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    cameraThread.lock();
    videoTexture.loadData(cameraThread.image);
    tracker.update(toCv(cameraThread.image));
    cameraThread.unlock();

//    position = tracker.getPosition();
//    scale = tracker.getScale();
//    orientation = tracker.getOrientation();
//    rotationMatrix = tracker.getRotationMatrix();
//    
    if(ofGetFrameNum()%60 == 0) {
        if (tracker.getFound()) {
            std::cout << "Tracker Found" << endl;
        }

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    shader.begin();
    shader.setUniformTexture("srcTex", videoTexture, 1);
    shader.setUniformTexture("noiseTex", noiseTex.getTexture(), 2);
    shader.setUniform2f("u_resolution", WIDTH, HEIGHT);
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    videoTexture.draw(0,0);
    shader.end();
    
//    if(tracker.getFound()) {
//        ofSetLineWidth(1);
//        tracker.draw();
//        
//        ofSetupScreenOrtho(640, 480, -1000, 1000);
//        ofTranslate(640 / 2, 480 / 2);
//        applyMatrix(rotationMatrix);
//        ofScale(5,5,5);
//        ofDrawAxis(scale);
//        tracker.getObjectMesh().drawWireframe();
//    }

    controller.drawMetrics(WIDTH, HEIGHT);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key=='l') {
        shader.load("distortion.vert", "distortion.frag");
    }
    
    if (key==OF_KEY_LEFT) {
        controller.setDate("20160314");
        controller.getMetricsForDay();
    }
    
    if (key==OF_KEY_RIGHT) {
        controller.setDate("20160315");
        controller.getMetricsForDay();
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    cameraThread.stop();
    controller.stop();
    tracker.stopThread();
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
