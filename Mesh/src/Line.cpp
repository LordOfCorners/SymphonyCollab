

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

void Line::draw(float _amp, int number) {
    width = _amp;
    
    int whiteness = 200- ofGetElapsedTimef()*10;
    if (whiteness < -1) whiteness = 0;
    //int whiteness = 200;
    if(number == 1){
        ofSetColor(255 + whiteness,
                   255 * (pos.y / ofGetHeight() + whiteness),
                   255 * (pos.x / ofGetWidth() /1.1 + whiteness),
                   30); //width * 40); //30);
    }
    if(number == 2){
       ofSetColor(255 * (pos.y / ofGetHeight() + whiteness),
                  100 + whiteness,
                  255 * (pos.x / ofGetWidth()/1.1 +whiteness),
                  30);// width*40); //30);
    }
    if(number == 3){
        ofSetColor(255 * (pos.y / ofGetHeight() + whiteness),
                   255 * (pos.x / ofGetWidth()/1.1 + whiteness),
                   255 + whiteness,
                   30); //width*40); //30 );
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