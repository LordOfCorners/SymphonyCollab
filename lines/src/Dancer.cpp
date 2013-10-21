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
    vel = ofVec2f( -0.5, 0.0 );
    
    // Create one line right off the bat.
    addLine();
}

void Dancer::addLine() {
    
    // This function creates an instance of the Line class, sets it up with current values, and adds it to the vector.
    Line tmp;
    tmp.setup( pos, 10 );
    lineList.push_back( tmp );
}

void Dancer::update() {
    
    // Move the pos (based on data, tempo, other?).
    pos += vel;
    
    // Add a new line every update.
    addLine();
    
    // Update the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
        lineList[i].update( c );
    }
}

void Dancer::draw() {
    
    // Draw the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
        lineList[i].draw();
    }
}