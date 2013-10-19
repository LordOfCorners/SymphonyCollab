#pragma once

#include "ofMain.h"

class Line {
public:
    // This will draw an individual line with length determined by breathing data.
    Line();

    void setup( ofVec2f _pos, float _rad );
    void draw();

    ofVec2f pos;
    float rad;
};


class testApp : public ofBaseApp
{

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

    Line myLine;

};
