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
    //    c = _c;
    
    rotSpeed = ofRandom(0.5, 1.0);
    angle = ofRandom(0,360);
    
    age = 0;
    lifespan = floor( ofRandom(60,100) );
    
}
void Particle::update(float _breathing, float _rotSpeed){
    
    angle += 0.9;
    angle +=  _rotSpeed;
    
    finalDia = offset + _breathing;
    
    //    pos += vel;
    //    vel += acc;
    acc.set(0);
    
    age++;
    if( age > lifespan){
        bIsDead = true;
    }
    
    float agePct = 1.0 - ((float)age / (float)lifespan);
    size = agePct * 3.0;
    
    
}

void Particle::draw(int colorNum){
    
    
    
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight() / 2);
    ofPushMatrix();{
        ofRotate(angle);
        ofTranslate(finalDia, 0);
        ofFill();
        
        if( colorNum == 0){
            ofSetColor(255);
            ofCircle(0,0, size*1.5);
            ofSetColor(255, 0, 50);
        }else if( colorNum == 1){
            ofSetColor(255);
        }else if( colorNum == 2){
            ofSetColor( 255, 127, 0);
        }
        ofCircle(0,0, size);
    }ofPopMatrix();
    ofPopMatrix();
    
    
    
    
    
    
    
}