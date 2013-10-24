#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    // First of all, clear out the vectors (in case of reset).
    // First the lineLists inside the dancerList...
    for ( int i = 0; i < dancerList.size(); i++) {
        dancerList[ i ].lineList.clear();
    }
    // ...then the dancerList itself.
    dancerList.clear();
    
    // Maintenance
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofSetCircleResolution( 100 );
    
    // May want to change this to a gradient or something else.
    ofBackground( 0 );
    
    // First dancer. Test/default values, to be overwritten later.
    pos = ofVec2f( ofRandomWidth(), ofRandomHeight() );
    vel = ofVec2f( -0.5, 0.5 );
    breath = 0;
    breathRad = 50;
    
    // Create a Dancer, feed in the pos and vel, and add it to the vector.
    Dancer instrument( pos, vel );
    dancerList.push_back( instrument );
}

//--------------------------------------------------------------
void testApp::update(){

    // First dancer.
    
    // Move the pos (based on data, tempo, other?). This will probably be rendered unnecessary if the data is used directly.
    /*vel.y += 0.01;
    vel.x += 0.01;*/
    
    
    // When we have real breathing data we won't need this, but for the time being, let's fake it.
    float waveSpeed = 1;
    breath = sin( ofGetElapsedTimef() * waveSpeed ) * breathRad;
    
    // Pass in the data and update the Dancers.
    for ( int i = 0; i < dancerList.size(); i++ ) {
        dancerList[ i ].update( breath );
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    for ( int i = 0; i < dancerList.size(); i++ ) {
        dancerList[ i ].draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    // Reset everything with 'r' (debug).
    if ( key == 'r' ) {
        setup();
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
