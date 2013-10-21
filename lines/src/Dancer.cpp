//
//  Dancer.cpp
//  lines
//
//  Created by J. Matthew Griffis on 10/21/13.
//
//

#include "Dancer.h"

Dancer::Dancer() {
    
    // Default is white (overwritten in update).
    c = ofColor( 255 );
}

void Dancer::setup() {
    
    // Test values.
    pos = ofGetWindowSize() / 2;
    vel = ofVec2f( -1.0, 0.0 );
}

void Dancer::update() {
    
    pos += vel;
}

void Dancer::draw() {
    
    ofSetColor( c );
    ofCircle( pos, 100 );
}