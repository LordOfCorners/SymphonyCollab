#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Line.h"
#include "Dancer.h"
#include "Particle.h"
#include "Orbit.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"

#define BUFFER_SIZE 512
#define NUMDANCERS 3
#define PORT 12345
#define NUMOFSTRINGS 20

class testApp : public ofBaseApp {
	
public:
    
    //--------------------------------------------------------------
    // THE BASICS
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    //--------------------------------------------------------------
    // CONTROL THE PARTS OF OUR APP
    void setupFFT();
    void updateFFT();
    void drawFFT();
    
    void setupLines();
    void updateLines();
    void drawLines();
    
    void setupOrbitsAndParticles();
    void updateOrbitsAndParticles();
    void drawOrbitsAndParticles();
    
    void setupWiFly();
    void updateWiFly();
    void drawWiFly();
    void calibrateWiFly();
    
    
    //--------------------------------------------------------------
    // LINES
    
    // One dancer per instrument (at least right now).
    
    float breath;
    float breathRad; // Temporarily simulate breathing.
    
    bool noiseBreath;
    
    vector< Dancer > dancerList;
    
    //--------------------------------------------------------------
    // ORBITS & PARTICLES
    
    //Use this to add random particles in different orbits
    //        void addParticle( int i );
    void addParticle(float dia);
    void addOrbit(float dia);
    
    vector < Particle > particleList;
    vector < Orbit > setOfOrbits;
    vector < float > diameterList;
    
    ofVec2f pos , vel, acc;
    float bandWidth;
    float rotSpeed[17], speed[17];
    float _size, rotDia, diaCoe, sinOfTime;
    ofColor particleColor;
    
    //Draw each different sets of orbits and particles on a different FBO
//    ofFbo mFbo, mFbo2, mFbo3;
    
    //--------------------------------------------------------------
    // WIFLY
    
    ofxUDPManager udpConnection;
    ofxUDPManager udpConnection2;
    ofxUDPManager udpConnection3;
    
    float x,x2, x3,xMapped, xMapped2, xMapped3;
    float sensorMin = 1023;
    float sensorMin2 = 1023;
    float sensorMin3 = 1023;
    float sensorMax = 0;
    float sensorMax2 = 0;
    float sensorMax3 = 0;
    
    //--------------------------------------------------------------
    //
    
    //---------------------------------------------------------------
    //OCS
    
    ofxOscReceiver mReceiver;
    int current_msg_string;
    string msg_strings[NUMOFSTRINGS];
    float timers[NUMOFSTRINGS];
    float amplitude[3], pitch[3], FFTavg[3][17], attack[3];
};

#endif

