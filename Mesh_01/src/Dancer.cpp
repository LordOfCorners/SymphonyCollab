
#include "Dancer.h"

Dancer::Dancer() {
    // Default constructor with no arguments.
}

Dancer::Dancer( ofVec2f _pos, ofVec2f _vel, int _number) {
    
    dancerNumber = _number;
    
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
    //tmp.setup( _pos, breath, angle );
    tmp.setup( _pos, thisBreath, angle );
    lineList.push_back( tmp );

}

void Dancer::update( float _breath, float _amplitude ) {
    
    thisBreath = _breath;
    
    //breath = _breath;
    amplitude = _amplitude;
    
    //cout<< "breath: "<<thisBreath<<endl;
    
    //breath = breath/10000.f; // .07 - .08
    
    // Bounce off the walls, for testing purposes.
    if ( pos.x < -200 || pos.x > ofGetWidth()+200 ) {
        vel.x *= -1;
    }
    if ( pos.y < -200 || pos.y > ofGetHeight()+200 ) {
        vel.y *= -1;
    }
    
    // Change the direction change, occasionally.
    if ( ofRandom( 1 ) < 0.1 ){
        if ( ofRandom( 1 ) < 0.2 ) {
            changeVel.x = ofRandom( -0.1, 0.1);
        }
    }
    if ( ofRandom( 1 ) < 0.1 ){
        if ( ofRandom( 1 ) < 0.2 ) {
            changeVel.y = ofRandom( -0.1, 0.1 );
        }
    }
    
    // Make the Dancer change direction.
    vel += changeVel;
    
    float velLimit = 1 * (ofGetElapsedTimef()/36);
    
    if(velLimit > 5) velLimit = 5;
    
    
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
//    cout<<"vel.x: "<< vel.x <<endl;
    angle = atan2( vel.y, vel.x );
    
    // Add a new line every update.
    addLine( pos );
    
    // Update the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        
//        lineList[i].update( c );
    }
    
    // Limit the size of the vector.
    
        //cout << "linelist: "<< lineList.size() << endl;

    if ( lineList.size() > MAXLINES ) {
        lineList.erase( lineList.begin() );
    }
}

void Dancer::draw() {
    
    // Draw the lines.
    for ( int i = 0; i < lineList.size(); i++ ) {
        lineList[i].draw(amplitude, dancerNumber);
    }
}