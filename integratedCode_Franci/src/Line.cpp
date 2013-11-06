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
    
    ofSetFrameRate(30);
    pos = _pos;
    length = _length;
    angle = _angle;
}

void Line::update() {
    
//    c = _c;
    
//    float pct = 0.1f;
//    float oldXMapped = xMapped-1;
//    xMapped = ofMap(x, sensorMin, sensorMax, 155, -100);
//    xMapped = (1-pct) * oldXMapped + (pct) * xMapped;

//    float pct = 0.0000001f;
//    ofVec2f oldpos = pos = - ofVec2f(1,1);
//    pos.x = (1-pct) * oldpos.x + (pct) * oldpos.x;
//    pos.y = (1-pct) * oldpos.y + (pct) * oldpos.y;
    
}

void Line::draw() {
    
    ofSetColor( 255, 255 * (pos.y / ofGetHeight() ), 255 * (pos.x / ofGetWidth() ), 10 );
    ofPushMatrix();{
        ofTranslate( pos );
        ofRotate( ofRadToDeg( angle ) * TWO_PI );
        ofSetLineWidth(40);
        ofLine( 0, ofRandom(-length, -length-100) , 0, ofRandom(length, length+100));
    }ofPopMatrix();
}