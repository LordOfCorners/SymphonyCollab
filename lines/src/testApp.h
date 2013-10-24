#pragma once

#include "ofMain.h"
#include "Line.h"
#include "Dancer.h"

#define NUMDANCERS 3

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // One dancer per instrument (at least right now).
    
    float breath;
    float breathRad; // Temporarily simulate breathing.
    
    bool noiseBreath;
    
    vector< Dancer > dancerList;
};
