#include "Line.h"

Line::Line()
{
    //ctor
}

Line::~Line()
{
    //dtor
}

void Line::setup( ofVec2f _pos, float _rad ) {

    pos = _pos;
    rad = _rad;
}

void Line::draw() {

    ofLine( pos.x, pos.y - rad, pos.x, pos.y + rad );
}

/*
#include "Line.h"

Line::Line() {

}

void Line::setup( ofVec2f _pos, float _rad ) {

    pos = _pos;
    rad = _rad;
}

void Line::draw() {

    ofLine( pos.x, pos.y - rad, pos.x, pos.y + rad );
}
*/
