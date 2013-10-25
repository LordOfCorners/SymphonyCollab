#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "fft.h"
#include "FFTOctaveAnalyzer.h"
#include "Line.h"
#include "Dancer.h"

#define BUFFER_SIZE 512
#define NUMDANCERS 3

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
    
    //--------------------------------------------------------------
    // FFT
    
    void audioReceived 	(float * input, int bufferSize, int nChannels);
	
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
    
    //--------------------------------------------------------------
    // 
};

#endif

