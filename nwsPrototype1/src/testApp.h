#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
<<<<<<< HEAD
#include "Dancer.h"
=======
#include "fft.h"
#include "FFTOctaveAnalyzer.h"
>>>>>>> 187afc4db125156ad149e3a8d77c4f33010a22f9

#define BUFFER_SIZE 512

class testApp : public ofBaseApp {
	
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
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
};

#endif

