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
#define MAXLINES 1000

class Dancer {
public:
    // This will be a vector of Line-class instances, feeding them the current pos, length and color, and controlling how many are displayed at once. Lines are "stupid"; the Dancer supplies the intelligence.
    Dancer();
    
    void setup( ofVec2f _pos );
    
    // Breath data gets passed in through the update to the addLine method to control the length of the line.
    void addLine( float breath );
    void update( float breath );
    
    void draw();
    
    ofVec2f pos, vel;
    
    ofColor c;
    
    vector< Line > lineList;
};