#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640, 480);
    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew()){
        tracker.update(ofxCv::toCv(grabber));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Draw the grabber
    grabber.draw(0,0);
    
    for(int i=0;i<tracker.numFaces();i++){
        
        // Draw debug pose
        tracker.drawPose(i);
        
        // Apply the pose matrix
        ofPushView();
        ofPushMatrix();
        tracker.applyPoseMatrix(i);
        
        // Draw sphere (0,0,0) is forehead
        ofDrawSphere(0, 0, 150, 20);
        
        ofPopMatrix();
        ofPopView();
    }
}
