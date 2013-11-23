//
//  Line.h
//  integratedCode
//
//  Created by Mauricio Sanchez Duque on 11/10/13.
//
//

#pragma once
#include "ofMain.h"

class Line{
    
public:
    
    Line();
    
    void setup();
    void draw();
    void update();
    
    ofPoint pos;
    vector  <ofPoint>   pointList;
    float radius;
};