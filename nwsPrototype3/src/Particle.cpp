//
//  Particle.cpp
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#include "Particle.h"

Particle::Particle( ofVec2f _pos, ofVec2f _vel, ofVec2f _acc, float _size, float _rotDia){
    
    
    size = _size;
    pos = _pos;
    vel = _vel;
    acc = _acc;
    rotDia = _rotDia;
    
    rotSpeed = ofRandom(0,3.0f);
        
    
}




void Particle::update(){
    
    float posCirx, posCiry;
    
    posCirx = sin( ofGetElapsedTimef() * rotSpeed);
    posCiry = cos( ofGetElapsedTimef() * rotSpeed);
    
    pos.x = posCirx * rotDia;
    pos.y = posCiry * rotDia;
    

//    pos += vel;
//    vel += acc;
    
//    acc.set(0);
    
    
    
}

void Particle::draw(){
    
    
    ofPushMatrix();{
    
        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight());
        ofFill();
        ofCircle(pos, size);
        
        
    }ofPopMatrix();
    
    
    
    
    
    
    
}