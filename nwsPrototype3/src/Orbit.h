//
//  Orbit.h
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#pragma once
#include "ofMain.h"
//#include "Particle.h"

class Orbit {
    
public:
    
    Orbit( ofVec2f _pos, float _dia);
    
    void update();
    
    void draw();
    
    ofVec2f pos;
    
    float dia;
    

    
};
