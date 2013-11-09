#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "fft.h"
#include "FFTOctaveAnalyzer.h"
#include "Line.h"
#include "Dancer.h"
#include "Particle.h"
#include "Orbit.h"
#include "ofxNetwork.h"
#include "aubioAnalyzer.h"

#define BUFFER_SIZE 512/2
#define NUMDANCERS 30

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
    
    // We started with one audio manipulation example (FFT) but then I introduced another (Aubio). -Matt
    void setupFFT();
    void setupAubio();
    void updateFFT();
    void updateAubio();
    void drawFFT();
    void drawAubio();
    
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
    // FFT
    
    void audioReceived 	(float * input, int bufferSize, int nChannels);
	
    // Subset: Aubio:
    
    float * leftAub;
    float * rightAub;
	
    aubioAnalyzer AA;
	
    ofTrueTypeFont dinFont;
    
    // Subset: not Aubio:
    
    FFTOctaveAnalyzer FFTanalyzer;
    
    float left[BUFFER_SIZE];
    float right[BUFFER_SIZE];
    
    fft		myfft;
    
    float magnitude[BUFFER_SIZE];
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    float freq[BUFFER_SIZE/2];
    
    
    float theta[18];
    float spin[18];
    
    //--------------------------------------------------------------
    // LINES
    
    // One dancer per instrument (at least right now).
    
    float breath;
    float breathRad; // Temporarily simulate breathing.
    
    bool noiseBreath;
    
    vector< Dancer > dancerList;
    
    // For debug purposes only:
    float test;
    float testVel;
    
    //--------------------------------------------------------------
    // ORBITS
    
    //Use this to add random particles in different orbits
    //        void addParticle( int i );
    void addParticle(float dia);
    void addOrbit(float dia);
    
    vector < Particle > particleList;
    vector < Orbit > setOfOrbits;
    vector < float > diameterList;
    
    ofVec2f pos , vel, acc;
    float _size, rotDia, diaCoe, sinOfTime;
    ofColor particleColor;

    
    //--------------------------------------------------------------
    // WIFLY
    
    ofxUDPManager udpConnection;
    ofxUDPManager udpConnection2;
    
    float x,x2,xMapped, xMapped2;
    float sensorMin = 1023;
    float sensorMin2 = 1023;;
    float sensorMax = 0;
    float sensorMax2 = 0;
    
    //--------------------------------------------------------------
    //
};

#endif

