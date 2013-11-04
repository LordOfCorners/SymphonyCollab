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
    
    changeVel = ofVec2f( 0.1, 0.1 );
    
    fillIn = true;
}

void Dancer::addLine( ofVec2f _pos ) {
    
    // This function creates an instance of the Line class, sets it up with current values, and adds it to the vector.
    Line tmp;
    tmp.setup( _pos, breath, angle );
    lineList.push_back( tmp );
    
//    if ( lineList.size() > 1 && fillIn) {
//        fillInGap();
//    }
}

//void Dancer::fillInGap() {
//    
//    // This function will detect if there is visible space between lines in the Dancer and fill the space with more lines, hopefully resulting in a more seamless look.
//    
//    // Calculate the difference in pos between the most recent line and the previous line.
//    int needLines = int( ofVec2f( lineList[ lineList.size() - 1 ].pos - lineList[ lineList.size() - 2 ].pos ).length() );
//    
//    // If it is greater than 1, i.e. the two lines are not touching, fill the gap with new lines.
//    if ( needLines > 1 ) {
//        for ( int i = 1; i < needLines; i++ ) {
//            addLine( ofVec2f( pos + ( vel.normalized() * i ) ) );
//        }
//    }
//}

void Dancer::update( float _breath ) {
    
    breath = _breath;
    
    // Bounce off the walls, for testing purposes.
    if ( pos.x < -200 || pos.x > ofGetWidth()+200 ) {
        vel.x *= -1;
    }
    if ( pos.y < -200 || pos.y > ofGetHeight()+200 ) {
        vel.y *= -1;
    }
    
    // Change the direction change, occasionally.
    if ( ofRandom( 1 ) < 0.1 ){
        if ( ofRandom( 1 ) < 0.5 ) {
            changeVel.x = ofRandom( -0.2, 0.2 );
        }
    }
    if ( ofRandom( 1 ) < 0.3 ){
        if ( ofRandom( 1 ) < 0.5 ) {
            changeVel.y = ofRandom( -0.1, 0.1 );
        }
    }
    
    // Make the Dancer change direction.
    vel += changeVel;
    
    float velLimit = 5;
    // Limit the vel.
    vel.limit( velLimit );
    if ( vel.y < -velLimit ) {
        vel.y = -velLimit;
    }
    if ( vel.x < -velLimit ) {
        vel.x = -velLimit;
    }
    
    pos += (vel * 0.9);
    
    // Set the rotation angle in the direction of movement.
    angle = atan2( vel.y, vel.x );
    
    // Add a new line every update.
    addLine( pos );
    
    // Update the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
//        lineList[i].update( c );
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