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
    
}




void Particle::update(float _breathing, float _rotSpeed){
    
    rotSpeed = _rotSpeed;
    
    float posCirx, posCiry;
    
    posCirx = sin( ofGetElapsedTimef() * rotSpeed );
    posCiry = cos( ofGetElapsedTimef() * rotSpeed );
    
    rotSpeed *= 0.97;
    
    
    float finalDia = offset + _breathing;
    
    pos.x = posCirx * finalDia;
    pos.y = posCiry * finalDia;
    

    pos += vel;
    vel += acc;
    acc.set(0);
    
    
}

void Particle::draw(){

    
    
    ofPushMatrix();{
        
        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight());
        ofFill();
        ofSetColor( c );
        ofCircle(pos, size);
        
        
    }ofPopMatrix();
    
    
    
    
    
    
    
}