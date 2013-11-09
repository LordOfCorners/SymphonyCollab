//
//  Particle.cpp
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#include "Particle.h"

Particle::Particle( ofVec2f _pos, ofVec2f _vel, ofVec2f _acc, float _size, float _rotDia, ofColor _c){
    
    offset = _rotDia;
    size = _size;
    pos = _pos;
    vel = _vel;
    acc = _acc;
    c = _c;
    
    rotSpeed = ofRandom(0.5, 1.0);
    angle = 0;
}




void Particle::update(float _breathing, float _rotSpeed){
    
    angle += 0.9;
    angle +=  _rotSpeed;
    finalDia = offset + _breathing;
    
    pos += vel;
    vel += acc; 
    acc.set(0);
    
    
    
    
}

void Particle::draw(){
    
    ofPushMatrix();
        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight() / 2);
        ofPushMatrix();{
            ofRotate(angle);
            ofTranslate(finalDia, 0);
            ofFill();
            ofSetColor( c );
            ofCircle(0,0, size);
        }ofPopMatrix();
    ofPopMatrix();
    
    
    
    
    
    
    
}