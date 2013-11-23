//
//  Boid.h
//  integratedCode
//
//  Created by Mauricio Sanchez Duque on 11/10/13.
//
//

#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Orbit.h"

class Boid {
    
public:
    
    Boid();
    
    void setup();
    void draw(int boidNum);
    void update(float fft[3][17]);
    
    vector < Particle > particleList;
    vector < Orbit > setOfOrbits;
    vector < float > diameterList;
    
    ofVec2f pos , vel, acc;
    float bandWidth;
    float rotSpeed[17], speed[17];
    float _size, rotDia, diaCoe, sinOfTime;
    ofColor particleColor;
    ofColor color[3];
    
    float max[17];
    vector < float> breathingData;
    
    float xMapped;
    int r;
   // float FFTavg[17];
    
private:
    
    void setupOrbitsAndParticles();
    void updateOrbitsAndParticles(float fft[3][17]);
    void drawOrbitsAndParticles(int boidNum);
    
    void addParticle(float dia);
    void addOrbit(float dia);
    
    
};
