//
//  Dancer.h
//  nwsPrototype1
//
//  Created by Mauricio Sanchez Duque on 10/5/13.
//
//


#pragma once
#include "ofMain.h"

class Dancer {
    
public:
    
    
    Dancer();
    void setup( ofVec2f rVel );
    void draw();
    void update();
    
    ofVec2f pos, vel;
    
    
    
private:
    
    
    
};