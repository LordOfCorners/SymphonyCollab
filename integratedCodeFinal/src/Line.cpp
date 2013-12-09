//
//  Line.cpp
//  integratedCode
//
//  Created by Mauricio Sanchez Duque on 11/10/13.
//
//

#include "Line.h"


//--------------------------------------------------------------
void Line::setup(){
    
    pos = ofGetWindowSize()/2;
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofBackground(0);
    
    
    
    
}

//--------------------------------------------------------------
void Line::update(){
    
}

//--------------------------------------------------------------
void Line::draw(){
    
    float angle = ofGetElapsedTimef() * 0.2;
    float radius = 75;
    
    float x = radius * cos(angle * 2) * TWO_PI;
    float y = radius * sin( angle * 2) * TWO_PI;
    
    ofPoint temp;
    temp.x = x;
    temp.y = y;
    pointList.push_back(temp);
    if( pointList.size() > 10 ){
        pointList.erase( pointList.begin());
    }
    
    for (int i=0; i<pointList.size(); i++) {
        ofPushMatrix();{
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
            ofRotateZ(ofGetElapsedTimef() * 0.5 * i );
            ofRotateX(ofGetElapsedTimef() * 1 * i );
            ofRotateY(ofGetElapsedTimef() * 1 * i );
            
            ofNoFill();
            ofSetColor(255,255,255, 10);
            ofSetLineWidth(2);
            ofLine(x, y, x-20, y+20);
            //ofCircle(x,y,100);
            
        }ofPopMatrix();
    }
    
    
    
}
