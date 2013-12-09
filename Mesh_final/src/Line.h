

#pragma once
#include "ofMain.h"

class Line {
public:

    Line();
    
    // Pos and length are static for each individual line.
    void setup( ofVec2f _pos, float _length, float _angle );
    // Color can change.
    void update(  );
    void draw( float _amplitude, int _number);
    
    ofVec2f pos;
    float length, angle;
    ofColor c;
    
    float width;
};