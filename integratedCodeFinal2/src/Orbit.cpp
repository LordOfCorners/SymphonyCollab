//
//  Orbit.cpp
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#include "Orbit.h"

Orbit::Orbit( ofVec2f _pos, float _dia){

    offset = _dia;
    pos = _pos;
    
}

void Orbit::update(float _breathing){
    
    dia = _breathing + offset ;
}

void Orbit::draw(){   
    
    ofNoFill();
    ofSetLineWidth(1.5);
//    ofSetColor(color,50);
    ofSetCircleResolution(100);
    ofCircle( pos, dia);
    
}