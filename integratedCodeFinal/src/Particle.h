//
//  Particle.h
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#pragma once
#include "ofMain.h"


class Particle{
    
    
public:
    
    Particle( ofVec2f _pos, ofVec2f _vel, ofVec2f _acc, float _size, float _rotDia);
    
    void update(float _breathing , float _rotSpeed );
    void draw(int colorNum);

    
    ofVec2f pos, vel, acc;
    
    float size;
    float rotSpeed, rotDia, offset, finalDia, angle;
    
    ofColor c;
    
    float age, lifespan;
    bool bIsDead;   
};

