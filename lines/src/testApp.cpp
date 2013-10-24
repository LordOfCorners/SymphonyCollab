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
    
    breath = 0;
    breathRad = 50;
    
    // Create Dancers, feed in a pos and vel, and add them to the vector.
    for ( int i = 0; i < NUMDANCERS; i++ ) {
        Dancer instrument( ofVec2f( ofRandomWidth(), ofRandomHeight() ),  ofVec2f( ofRandom( -0.5, 0.5 ), ofRandom( -0.5, 0.5 ) ) );
        dancerList.push_back( instrument );
    }
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Set the color back to default.
    dancerList[ 0 ].c.set( ofColor( 255, 0, 0 ) );
    dancerList[ 1 ].c.set( ofColor( 0, 255, 0 ) );
    dancerList[ 2 ].c.set( ofColor( 0, 0, 255 ) );
    
    // Change the color upon collision. This isn't working right now and it also makes the app run really slowly, so I'm turning it off.
    /*for ( int i = 0; i < dancerList.size(); i++ ) {
        for ( int j = 0; j < dancerList.size(); j++ ) {
            for ( int k = 0; k < dancerList[ i ].lineList.size(); k++ ) {
                for ( int l = 0; l < dancerList[ j ].lineList.size(); l++ ) {
                    if ( dancerList[ i ].lineList[ k ].pos == dancerList[ j ].lineList[ l ].pos ) {
                        dancerList[ i ].lineList[ k ].c = ofColor(255);
                        dancerList[ j ].lineList[ l ].c = ofColor(255);
                    }
                }
            }
        }
    }*/
    
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
    
    // Toggle "fill in" mode on and off.
    if ( key == '1' ) {
        for ( int i = 0; i < dancerList.size(); i++ ){
            dancerList[ i ].fillIn = !dancerList[ i ].fillIn;
        }
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
