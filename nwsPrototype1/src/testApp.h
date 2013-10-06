#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "fft.h"
#include "FFTOctaveAnalyzer.h"
#include "Dancer.h"

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
    
    
    /* Things we could work with:
     pitch ( amplitude and frequency )
     volume
     difference between notes
     time between notes
     total time
     harmony/dissonance
     how many instruments playing at once
     breathing--regularity
     */

    
    //------------------------Dancer functions and variables ---------
    
    //We use this function to add as many dancer as we want
    void addDancer();
    
    //Here we initiate our dancer
    vector < Dancer > newDancer;
    
    
};

#endif	

