//
//  Particle.cpp
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#include "Particle.h"

Particle::Particle( ofVec2f _pos, ofVec2f _vel, ofVec2f _acc, float _size, float _rotDia){
    
    offset = _rotDia;
    size = _size;
    pos = _pos;
    vel = _vel;
    acc = _acc;
    
    rotSpeed = ofRandom(0,3.0f);
        
    
}




void Particle::update(float _breathing){
    
    float posCirx, posCiry;
    
    posCirx = sin( ofGetElapsedTimef() * rotSpeed);
    posCiry = cos( ofGetElapsedTimef() * rotSpeed);
    
    
    float finalDia = offset + _breathing;
    
    pos.x = posCirx * finalDia;
    pos.y = posCiry * finalDia;
    

    pos += vel;
    vel += acc;
    
//    acc.set(0);
    
    
    
}

void Particle::draw(){

    
    //Mauricio: I was trying to get trail effect. But if I draw this in the testApp.cpp it does not work. Only if it is here for some reason.
        ofPushMatrix();{
        
        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight());
        ofFill();
        ofSetColor(255);
        ofCircle(pos, size);
        
        
    }ofPopMatrix();
    
    
    
    
    
    
    
}