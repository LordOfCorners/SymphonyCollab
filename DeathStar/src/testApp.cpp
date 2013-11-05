// based on Gustavo Faria's code

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    pos = ofGetWindowSize()/2;
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    mFbo.allocate( ofGetWindowWidth(), ofGetWindowHeight() );
    
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofBackground(0);

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
//    cam.begin();
    mFbo.begin();

    
    float angle = ofGetElapsedTimef() * 0.2;
    float radius = 75;
    
    float x = radius * sin( angle * 2) * TWO_PI;
    float y = radius * cos( angle * 2) * TWO_PI;
    float z = radius * cos( angle * 2) * TWO_PI;

    
    ofPoint temp;
    temp.x = x;
    temp.y = y;
    temp.z = z;
    
    pointList.push_back(temp);
    if( pointList.size() > 10 ){
        pointList.erase( pointList.begin());
    }
    
    for (int i=0; i<pointList.size(); i++) {
        ofPushMatrix();{
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
            ofRotateZ(ofGetElapsedTimef() * 0.7 * i );
            ofRotateX(ofGetElapsedTimef() * 1 * i );
            ofRotateY(ofGetElapsedTimef() * 1 * i );
        
            ofNoFill();
            ofSetColor(255 ,255, 255, 20 );
            ofSetLineWidth(1
                           );
            ofLine(x, y, x-30, y+30);
            //ofCircle(x,y,100);
            
        }ofPopMatrix();
    }
    
    mFbo.end();
    
    mFbo.draw(0,0);
    mFbo.draw(0,20);
//    mFbo.draw(20,20);
//    mFbo.draw(20,0);
    
//    cam.end();

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
