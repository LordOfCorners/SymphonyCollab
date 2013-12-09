//
//  Boid.cpp
//  integratedCode
//
//  Created by Mauricio Sanchez Duque on 11/10/13.
//
//

#include "Boid.h"

Boid::Boid(){
    
}

void Boid::setup(){
    
    setupOrbitsAndParticles();
    color[0] =ofColor(255,255,255);
    color[1] =ofColor(100,0,200);
    color[2] =ofColor(0,100,255);
    
    
}

void Boid::update(float fft[3][17]){
    
    updateOrbitsAndParticles(fft);
    
}

void Boid::draw(int boidNum){
    
    if(boidNum == 0){
        
        ofSetColor(color[0]);
    }
    
    else if(boidNum == 1){
        
        ofSetColor(color[1]);
    }
    
    else if(boidNum == 2){
        
        ofSetColor(color[2]);
    }
    drawOrbitsAndParticles(boidNum);
    
}

void Boid::setupOrbitsAndParticles(){
    
    particleList.clear();
    setOfOrbits.clear();
    
    //We get the diameter of our Orbits
    for( int i = 0 ; i < 17; i++){
        
        float coe = 1.01 * powf( 1.15, i);
        float _orbit = 25;
        diameterList.push_back( _orbit * coe);
        
    }
    
    for( int i = 0; i < 17; i++){
        
        _size = ofRandom(5, 10);
        pos.set(ofRandom(ofGetWindowWidth() / 2), ofRandom(ofGetWindowHeight()));
        vel.set(ofRandom(.9));
        //        particleColor.set(ofRandom(255),ofRandom(255),ofRandom(255));
        
        addOrbit(diameterList[i]);
        addParticle(diameterList[i]);
        
    }
}

void Boid::addParticle(float dia){
    
    Particle p( pos, vel, acc, _size, dia);
    particleList.push_back(p);
    
}
void Boid::addOrbit(float dia){
    
    Orbit tmp( ofPoint( ofGetWindowWidth()/2, ofGetWindowHeight()/ 2), dia);
    setOfOrbits.push_back( tmp);
    
}
void Boid::updateOrbitsAndParticles(float fft[3][17]){
    
    //Draw the orbits
    vector<Orbit>::iterator o;
    for( o = setOfOrbits.begin(); o != setOfOrbits.end(); o++){
        
        o->update(xMapped);
    }
    
    //This creates more particles according to the volume on each frequency
    for( int i = 0; i < 17; i++){
        
        if( fft[r][i] > 0.9f){
            addParticle(diameterList[i]);
        }
    }
    
    for (int i =0; i < 17; i++){
        speed[i] = ofMap(fft[r][i],0, 24, 0, 10, true);
        rotSpeed[i] = speed[i];
        rotSpeed[i] *= 0.8;
    }
    //Draw the Particles
    for (vector < Particle >::iterator it = particleList.begin(); it != particleList.end();) {
        
        if( it->bIsDead){
            //If dead erase
            particleList.erase(it);
            
        }else{
            
            for (int i = 0; i<diameterList.size(); i++) {
                //If located on the right diameter. Relationship between the position of the orbits and the the particles
                if (it->offset == diameterList[i]) {
                    it->update(xMapped, rotSpeed[i]);
                };
            };
            //Keep moving to the next iterator
            it++;
        }
    }
    
}
void Boid::drawOrbitsAndParticles(int boidNum){
    
    vector<Orbit>::iterator p;
    for( p = setOfOrbits.begin(); p != setOfOrbits.end(); p++){
        
        p->draw();
        
    }
    
    
    vector<Particle>::iterator it;
    for( it = particleList.begin(); it != particleList.end(); it++){
        
        it->draw(boidNum);
        //        ofDrawBitmapString(ofToString(rotSpeed[i]), 180, i * 20);
        
        //This index goes at the end so that when it loops for the first time it takes 0 as a value and not one
        
    }
    
}
