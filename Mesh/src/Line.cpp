

#include "Line.h"

Line::Line() {
    
    // Default is white (overwritten in update).
    c = ofColor( 255 );
}

void Line::setup( ofVec2f _pos, float _length, float _angle ) {
    
    ofSetFrameRate(30);
    //pos = _pos;
    pos = _pos;
    //cout << "pos: "<<pos<<endl;
    length = _length;
    //angle = _angle;
    angle = _angle * 0.005 * ofGetElapsedTimef();
    
}

void Line::update() {

    
}

void Line::draw(float _amplitude, int number) {
    width = _amplitude;
    
    int whiteness = 200 - ofGetElapsedTimef() * 4;
    if (whiteness < 1) whiteness = 0;
    //int whiteness = 200;
    
//    cout << "whiteness" << whiteness ;
    
    if(number == 1){
        ofSetColor(255,
                   255 * (pos.y / ofGetHeight()) + whiteness,
                   255 * (pos.x / ofGetWidth()) + whiteness,
                   width*20); //30);
    }
    if(number == 2){
       ofSetColor(255  * (pos.y / ofGetHeight()) + whiteness,
                  100 * (pos.x / ofGetWidth()) + whiteness,
                  255,
                  width*20); //30);
        //cout<<pos.x / ofGetWidth() +whiteness<<endl;
    }
    if(number == 3){
        ofSetColor(100 * (pos.x / ofGetWidth()) + whiteness,
                   255 * (pos.y / ofGetHeight()) + whiteness,
                   //50+pos.x / ofGetWidth() + whiteness,
                   //50+ (pos.y / ofGetHeight()) + whiteness,
                   255,
                   width*20); //30 );
        //cout<<pos.y / ofGetWidth() +whiteness<<endl;
    }
    
    //ofSetColor(255, 255 * (pos.y / ofGetHeight()), 255 * (pos.y / ofGetWidth()), 30);
    
    //cout << "angle: "<<angle <<endl;
    
    ofPushMatrix();{
        ofTranslate( pos );
        ofRotate( ofRadToDeg( angle ) * TWO_PI );
        ofSetLineWidth(1);
        //ofLine( 0, ofRandom(-length, -length-100) , 0, ofRandom(length, length+100));
        ofLine(0, -length - (ofRandom(30)), 0, length + ofRandom(30));
    }ofPopMatrix();
}