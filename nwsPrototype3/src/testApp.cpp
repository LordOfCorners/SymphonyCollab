#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSeedRandom();
    ofBackground( 0);
    
    
    //    acc.set(0);
    
    for( int i = 0; i < 18; i++){
        
        _size = ofRandom(2, 5);
        pos.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
        vel.set(ofRandom(0,.9));
        rotDia = ofRandom(100,800);
        addParticle();
        addOrbit();
        
        
    }
    
    
    
    
}

void testApp::addParticle(){
    
    Particle p( pos, vel, acc, _size, rotDia);
    particleList.push_back(p);
    
//    rotDia = setOfOrbits[i].dia;
}

void testApp::addOrbit(){
    
    Orbit tmp( ofPoint( ofGetWindowWidth()/2, ofGetWindowHeight ()), rotDia);
    setOfOrbits.push_back( tmp);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    vector<Particle>::iterator it;
    for( it = particleList.begin(); it != particleList.end(); it++){
        
        it->update();
    }
    
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    vector<Particle>::iterator it;
    for( it = particleList.begin(); it != particleList.end(); it++){
        
        it->draw();
    }
    
    
    vector<Orbit>::iterator p;
    for( p = setOfOrbits.begin(); p != setOfOrbits.end(); p++){
        
        p->draw();
    }
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
    
//    if ( ofRandom( 1 ) < 0.01 ) {
//        if ( /* music is high frequency*/ ) {
//            i = 12;
//        }
//        else if ( /* music is low frequency */) {
//            i = 2;
//        }
//        addParticle( i );
//    }
    
    addParticle();
    
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
