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

#define MAXLINES 500 // Limit the vector size.

class Dancer {
public:
    // This will be a vector of Line-class instances, feeding them the current pos, length and color, and controlling how many are displayed at once. Lines are "stupid"; the Dancer supplies the intelligence.
    Dancer();
    Dancer( ofVec2f _pos, ofVec2f _vel );
    
    // Breath data gets passed in through the update to the addLine method to control the length of the line.
    void addLine();
    void update( float _breath );
    
    void draw();
    
    ofVec2f pos, vel;
    
    float breath, angle;
    
    ofColor c;
    
    vector< Line > lineList;
};