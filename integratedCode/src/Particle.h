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
    
    Particle( ofVec2f _pos, ofVec2f _vel, ofVec2f _acc, float _size, float _rotDia, ofColor _c);
    
    void update(float _breathing , float _rotSpeed );
    void draw();
    
    ofVec2f pos, vel, acc;
    
    float size;
    float rotSpeed, rotDia, offset, finalDia, angle;
    
    ofColor c;
    
<<<<<<< HEAD
    float age, lifespan;
    bool bIsDead;
    
    
    
    

    
=======
    int age, lifespan;
    bool bIsDead;
>>>>>>> 141cf61acd2246c8c47145334110642a567d13e7
};

