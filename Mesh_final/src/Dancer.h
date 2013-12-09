
#pragma once

#include "ofMain.h"
#include "Line.h"

#define MAXLINES 400 // Limit the vector size.

class Dancer {
public:
    // This will be a vector of Line-class instances, feeding them the current pos, length and color, and controlling how many are displayed at once. Lines are "stupid"; the Dancer supplies the intelligence.
    Dancer();
    Dancer( ofVec2f _pos, ofVec2f _vel, int _number );
    
    void addLine( ofVec2f _pos );
    // Breath data gets passed in through the update to the addLine method to control the length of the line.
    void update( float _breath, float _amplitude );
    void draw();
    
    ofVec2f pos, vel, changeVel;
    float breath, angle, amplitude;
    ofColor c;
    bool fillIn;
    
    
    float thisBreath;
    vector< Line > lineList;
    
    int dancerNumber; // are we 1, 2, or 3
};