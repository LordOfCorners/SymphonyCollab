#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // Maintenance
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofSetCircleResolution( 100 );
    
    // May want to change this to a gradient or something else.
    ofBackground( 0 );
    
    breath = 0;
    breathRad = 50;
    
    myDancer.setup();
}

//--------------------------------------------------------------
void testApp::update(){

    // When we have real breathing data we won't need this, but for the time being, let's fake it.
    float waveSpeed = 0.5;
    breath = sin( ofGetElapsedTimef() * waveSpeed ) * breathRad;
    
    // Pass in the breathing data.
    myDancer.update( breath );
}

//--------------------------------------------------------------
void testApp::draw(){

    myDancer.draw();
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
