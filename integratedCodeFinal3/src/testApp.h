#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"
#include "Boid.h"


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
    
    void setupOrbitsAndParticles();
    void updateOrbitsAndParticles();
    void drawOrbitsAndParticles();
    
    void setupWiFly();
    void updateWiFly();
    void drawWiFly();
    void calibrateWiFly();
    
    Boid cir[3];
    
       
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
   // ofFbo mFbo, mFbo2, mFbo3;
    
    //--------------------------------------------------------------
    // WIFLY
    
    ofxUDPManager udpConnection;
    ofxUDPManager udpConnection2;
    ofxUDPManager udpConnection3;
    
//    float x,x2, x3,xMapped, xMapped2, xMapped3;
    float x[3], xMapped[3], sensorMin[3], sensorMax[3], oldXMapped[3];
//    float sensorMin;
//    float sensorMin2;
//    float sensorMin3;
//    float sensorMax;
//    float sensorMax2;
//    float sensorMax3;
    
//    float oldXMapped;
    vector < float> breathingData;
    float newX[3], sum[3];
    bool fakeBreath[3];
    
    //--------------------------------------------------------------
    //
    
    //---------------------------------------------------------------
    //OCS
    
    void getOfc();
    ofxOscReceiver mReceiver;
    int current_msg_string;
    string msg_strings[NUMOFSTRINGS];
    float timers[NUMOFSTRINGS];
    float amplitude[3], pitch[3], attack[3];
    float FFTavg[3][17];
    int Channel01_FFT_size;
    float max[17];
    
    ofxSyphonServer syphon;
    
    float imageCounter;

};
#endif

