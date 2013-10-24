//
//  Dancer.cpp
//  lines
//
//  Created by J. Matthew Griffis on 10/21/13.
//
//

#include "Dancer.h"

Dancer::Dancer() {
    // Default constructor with no arguments.
}

Dancer::Dancer( ofVec2f _pos, ofVec2f _vel ) {
    
    // Test/default values, to be overwritten later.
    /*pos = ofGetWindowSize() / 2;
    vel = ofVec2f( -0.5, 1.0 );*/
    pos = _pos;
    vel = _vel;
    breath = angle = 0;
    
    // Default is white (overwritten in update).
    c = ofColor( 255 );
    
    changeVel = ofVec2f( 0.01, 0.01 );
}

void Dancer::addLine() {
    
    // This function creates an instance of the Line class, sets it up with current values, and adds it to the vector.
    Line tmp;
    tmp.setup( pos, breath, angle );
    lineList.push_back( tmp );
}

void Dancer::update( float _breath ) {
    
    breath = _breath;
    
    // Bounce off the walls, for testing purposes.
    if ( pos.x < 0 || pos.x > ofGetWidth() ) {
        vel.x *= -1;
    }
    if ( pos.y < 0 || pos.y > ofGetHeight() ) {
        vel.y *= -1;
    }
    
    // Change the direction change, occasionally.
    if ( ofRandom( 1 ) < 0.1 ){
        if ( ofRandom( 1 ) < 0.5 ) {
            changeVel.x = ofRandom( -0.1, 0.1 );
        }
    }
    if ( ofRandom( 1 ) < 0.1 ){
        if ( ofRandom( 1 ) < 0.5 ) {
            changeVel.y = ofRandom( -0.1, 0.1 );
        }
    }
    
    // Make the Dancer change direction.
    vel += changeVel;
    
    // Limit the vel.
    vel.limit( 5);
    if ( vel.y < -5 ) {
        vel.y = -5;
    }
    if ( vel.x < -5 ) {
        vel.x = -5;
    }
    
    pos += vel;
    
    // Set the rotation angle in the direction of movement.
    angle = atan2( vel.y, vel.x );
    
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
}

void Dancer::draw() {
    
    // Draw the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
        lineList[i].draw();
    }
}