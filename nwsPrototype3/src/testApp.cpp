#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    ofSeedRandom();
  
    
    for( int i = 0; i < 17; i++){
        
        
         float coe = 1.02 * powf(1.19, i);
        float _orbit;
        _orbit = (rotDia + 40);
        diameterList.push_back( _orbit * coe );
        
    }
    
    for( int i = 0; i < 17; i++){
        
        _size = ofRandom(2, 5);
        pos.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
        vel.set(ofRandom(0,.9));
       
        
        
        addOrbit(diameterList[i] );
        addParticle(diameterList[i] );
    }
    
}

void testApp::addParticle(float dia){
    
    
    Particle p( pos, vel, acc, _size, dia);
    
    
//    if( ofRandom(1) < )
    particleList.push_back(p);
    

}

void testApp::addOrbit(float dia){
    
    Orbit tmp( ofPoint( ofGetWindowWidth()/2, ofGetWindowHeight ()), dia);
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
    
    
    ofEnableAlphaBlending();
    ofBackgroundGradient(50,0);
    
    
    vector<Particle>::iterator it;
    for( it = particleList.begin(); it != particleList.end(); it++){
        
        ofEnableAlphaBlending();
        ofBackgroundGradient(50,0);
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
    
    addParticle(diameterList[6]);
    
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
