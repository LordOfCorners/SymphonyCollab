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
    
    // Test/default values, to be overwritten later.
    pos = ofGetWindowSize() / 2;
    vel = ofVec2f( -0.5, 0.0 );
    
    // Create one line right off the bat with zero length (since we have no initial breathing data).
    addLine( 0 );
}

void Dancer::addLine( float breath ) {
    
    // This function creates an instance of the Line class, sets it up with current values, and adds it to the vector.
    Line tmp;
    tmp.setup( pos, breath );
    lineList.push_back( tmp );
}

void Dancer::update( float breath ) {
    
    // Move the pos (based on data, tempo, other?).
    pos += vel;
    
    // Add a new line every update.
    addLine( breath );
    
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