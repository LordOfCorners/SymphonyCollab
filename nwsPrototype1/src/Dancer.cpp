//
//  Dancer.cpp
//  nwsPrototype1
//
//  Created by Mauricio Sanchez Duque on 10/5/13.
//
//

#include "Dancer.h"



Dancer::Dancer(){
    
}

void Dancer::setup( ofVec2f rVel){
  
    vel = rVel;
    
    pos = ofGetWindowSize()/2;
    
    
}

void Dancer::update(){
    
    
    //We want our dancer to move smoothly so we initiate Noise in respect of time
    float noise = ofNoise( pos.x * 0,005, pos.y * 0.005, ofGetElapsedTimef() * 0.1) * 15.0;
    
    
    //We cast por noise into our position usin sin and cos so it moves in circles
    pos += ofVec2f( cos(noise), sin(noise));
    pos += vel;
//    //We want the speed to start slowing down a bit
//    vel *= 0.97;
    
    
    
}


void Dancer::draw(){
    
    //We finally draw our circle
    ofCircle( pos, 30.0);
    
}




