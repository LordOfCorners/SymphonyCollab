#ifndef LINE_H
#define LINE_H

#include "ofMain.h"

class Line
{
    public:
        Line();
        virtual ~Line();

        // This will draw an individual line with length determined by breathing data.
    //Line();

    void setup( ofVec2f _pos, float _rad );
    void draw();

    ofVec2f pos;
    float rad;

    protected:
    private:
};

#endif // LINE_H

/*#pragma once
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

*/
