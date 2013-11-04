//
//  Line.h
//  lines
//
//  Created by J. Matthew Griffis on 10/21/13.
//
//

#pragma once
#include "ofMain.h"

class Line {
public:
    // This will create a single verticle line at the current pos (which is moving). By storing each line in a vector (using a different class) and adjusting the length of the line based on breathing data, we can create an organic-looking continuous shape with shifting thickness. We can also rotate the lines to change direction.
    Line();
    
    // Pos and length are static for each individual line.
    void setup( ofVec2f _pos, float _length, float _angle );
    // Color can change.
    void update(  );
    void draw();
    
    ofVec2f pos;
    float length, angle;
    ofColor c;
};