//
//  Dancer.h
//  lines
//
//  Created by J. Matthew Griffis on 10/21/13.
//
//

#pragma once
#include "ofMain.h"
#include "Line.h"

class Dancer {
public:
    // This will be a vector of Line-class instances, feeding them the current pos, length and color, and controlling how many are displayed at once. Lines are "stupid"; the Dancer supplies the intelligence.
    Dancer();
    
    void setup();
    void addLine();
    void update();
    void draw();
    
    ofVec2f pos, vel;
    
    // This controls the length of the current Line based on breathing data.
    float breath;
    
    ofColor c;
    
    vector< Line > lineList;
};