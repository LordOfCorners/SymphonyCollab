#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // Maintenance
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofSetCircleResolution( 100 );
    
    // May want to change this to a gradient or something else.
    ofBackground( 0 );
    
    // First dancer. Test/default values, to be overwritten later.
    pos = ofVec2f( ofRandomWidth(), ofRandomHeight() );
    vel = ofVec2f( -0.5, 0.0 );
    breath = 0;
    breathRad = 50;
    myDancer.setup();
}

//--------------------------------------------------------------
void testApp::update(){

    // First dancer.
    
    // Move the pos (based on data, tempo, other?). This will probably be rendered unnecessary if the data is used directly.
    pos += vel;
    
    // When we have real breathing data we won't need this, but for the time being, let's fake it.
    float waveSpeed = 0.5;
    breath = sin( ofGetElapsedTimef() * waveSpeed ) * breathRad;
    
    // Pass in all the data.
    myDancer.update( pos, vel, breath );
}

//--------------------------------------------------------------
void testApp::draw(){

    myDancer.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    // Reset everything with 'r' (debug).
    if ( key == 'r' ) {
        setup();
        myDancer.lineList.clear();
    }
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
