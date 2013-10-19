#pragma once
#include "ofMain.h"

class Line {
public:
    // This will draw an individual line whose length is det
    Line();

    void setup();
    void update();
    void draw();

    ofVec2f pos, vel;
};
