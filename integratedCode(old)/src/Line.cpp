//
//  Line.cpp
//  lines
//
//  Created by J. Matthew Griffis on 10/21/13.
//
//

#include "Line.h"

Line::Line() {
    
    // Default is white (overwritten in update).
    c = ofColor( 255 );
}

void Line::setup( ofVec2f _pos, float _length, float _angle ) {
    
    pos = _pos;
    length = _length;
    angle = _angle;
}

void Line::update(  ofColor _c ) {
    
    c = _c;
}

void Line::draw() {
    
    ofSetColor( c );
    ofPushMatrix();{
        ofTranslate( pos );
        ofRotate( ofRadToDeg( angle ) );
        ofLine( 0, -length, 0, length );
    }ofPopMatrix();
}