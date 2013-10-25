//
//  Orbit.cpp
//  nwsPrototype3
//
//  Created by Mauricio Sanchez Duque on 10/19/13.
//
//

#include "Orbit.h"

Orbit::Orbit( ofVec2f _pos, float _dia){

    dia = _dia;
    pos = _pos;

    
}

void Orbit::update(){
    
    
}

void Orbit::draw(){
    
    ofNoFill();
    ofSetColor(255);
    ofSetCircleResolution(100);
    
    ofCircle( pos, dia);
    
   
}