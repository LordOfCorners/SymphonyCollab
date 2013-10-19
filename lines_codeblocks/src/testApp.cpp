#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // Maintenance
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofBackground( 0 );

    myLine.setup( ofGetWindowSize() / 2, 100 );

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    myLine.draw();
}

Line::Line() {

}

void Line::setup( ofVec2f _pos, float _rad ) {

    pos = _pos;
    rad = _rad;
}

void Line::draw() {

    ofLine( pos.x, pos.y - rad, pos.x, pos.y + rad );
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
