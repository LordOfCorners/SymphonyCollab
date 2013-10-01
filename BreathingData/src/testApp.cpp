#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    
    breathVal=0;
}

//--------------------------------------------------------------
void testApp::update(){
    sinOfTime = sin(ofGetElapsedTimef());
    sinOfTimeMapped = ofMap(sinOfTime,-1,1,0,300);
    ofLog(OF_LOG_NOTICE, "Breathing rate: " + ofToString(sinOfTimeMapped));
}

//--------------------------------------------------------------
void testApp::draw(){

    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight());
    ofScale(1,-1,1);
    ofRect(0, 0,30,sinOfTimeMapped);
    ofPopMatrix();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
