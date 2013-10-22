//
//  Dancer.cpp
//  lines
//
//  Created by J. Matthew Griffis on 10/21/13.
//
//

#include "Dancer.h"

Dancer::Dancer() {
    
    // Test/default values, to be overwritten later.
    pos = posPrev = ofGetWindowSize() / 2;
    vel = ofVec2f( -0.5, 1.0 );
    breath = angle = 0;
    
    // Default is white (overwritten in update).
    c = ofColor( 255 );
}

void Dancer::addLine() {
    
    // This function creates an instance of the Line class, sets it up with current values, and adds it to the vector.
    Line tmp;
    tmp.setup( pos, breath, angle );
    lineList.push_back( tmp );
}

void Dancer::update( ofVec2f _pos, ofVec2f _vel, float _breath ) {
    
    pos = _pos;
    vel = _vel;
    breath = _breath;
    
    // Prepare for rotation.
    calcAngle();
    
    // Add a new line every update.
    addLine();
    
    // Update the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
        lineList[i].update( c );
    }
    
    // Limit the size of the vector.
    if ( lineList.size() > MAXLINES ) {
        lineList.erase( lineList.begin() );
    }
    
    // Store the current position (which will become the previous position next cycle).
    posPrev = pos;
}

void Dancer::calcAngle() {
    
    float dy = pos.y - posPrev.y;
    float dx = pos.x - posPrev.x;
    angle = atan2( dy, dx );
    
    
}

void Dancer::draw() {
    
    // Draw the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
        lineList[i].draw();
    }
}