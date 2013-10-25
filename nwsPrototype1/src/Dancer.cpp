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
    
//    pos = ofGetWindowSize()/2;
    
    size = 5;
    
    spiralCoe = 10;
    
    posTo = ofGetWindowSize()/2;
    
    spiralCoeVel = .5;
    
    speedRoundCir = 5;
}

void Dancer::update(){
    
    
    posCirX = sin( ofGetElapsedTimef() * speedRoundCir );
    posCirY = cos ( ofGetElapsedTimef() * speedRoundCir );
    
    //We want our dancer to move smoothly so we initiate Noise in respect of time
    float noise = ofNoise( pos.x * 0.005, pos.y * 0.005, ofGetElapsedTimef() * 0.1) * 15.0;
    
    
    //We cast por noise into our position usin sin and cos so it moves in circles
    //    pos += ofVec2f( cos(noise), sin(noise));
    //    pos += vel;
    //    //We want the speed to start slowing down a bit
    //    vel *= 0.97;
    
    pos.x = posCirX * spiralCoe;
    pos.y = posCirY * spiralCoe;
    
    //This is the noise for the position at which the particle rotates in respect to.
    float noiseToPos = ofNoise( posTo.x * 0.0005, posTo.y * ofGetElapsedTimef() *0.1) * 10.0;
    
//    posTo += ofVec2f( cos( noiseToPos), sin( noiseToPos ));
    
//    posTo += vel;
    
    // Only change the velocity once in a while (determined randomly).
    if ( ofRandom( 1 ) < 0.01 ) {
        vel.x *= -1;
    }
    
    if ( ofRandom( 1 ) < 0.01 ) {
        vel.y *= -1;
    }
    
    spiralCoe += spiralCoeVel;
    
    if( spiralCoe > 50 || spiralCoe < 10){
        
        spiralCoeVel *= -1;
        
    }
    
    
    if( posTo.x < size || posTo.x > ofGetWindowWidth() - size){
        
        vel.x = -vel.x;
    }
    
    if( posTo.y < size || posTo.y > ofGetWindowHeight() - size){
        
        vel.y = -vel.y;
    }
    
    
}


void Dancer::draw(){
    
   
    
    
    ofPushMatrix();{
//         float noise = ofNoise( pos.x * 0,005, pos.y * 0.005, ofGetElapsedTimef() * 0.1) * 15.0);
        
        ofTranslate( posTo );
        //We finally draw our circle
        ofCircle( pos, size);
    }ofPopMatrix();
    
}




