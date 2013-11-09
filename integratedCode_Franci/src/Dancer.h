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

#define MAXLINES 400 // Limit the vector size.

class Dancer {
public:
    // This will be a vector of Line-class instances, feeding them the current pos, length and color, and controlling how many are displayed at once. Lines are "stupid"; the Dancer supplies the intelligence.
    Dancer();
    Dancer( ofVec2f _pos, ofVec2f _vel );
    
    void addLine( ofVec2f _pos );
//    void fillInGap();
    
    // Breath data gets passed in through the update to the addLine method to control the length of the line.
    void update( float _breath );
    
    void draw( float _freq );
    
    ofVec2f pos, vel, changeVel;
    
    float breath, angle;
    
    ofColor c;
    
    bool fillIn;
    
    vector< Line > lineList;
};