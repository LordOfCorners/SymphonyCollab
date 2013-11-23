#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Line.h"
#include "Dancer.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxSyphon.h"

#define BUFFER_SIZE 512
#define NUMDANCERSONE 10
#define NUMDANCERSTWO 10
#define NUMDANCERSTHREE 10

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
    
    void setupLines();
    void updateLines();
    void drawLines();
    
    void setupWiFly();
    void updateWiFly();
    void drawWiFly();
    void calibrateWiFly();
    
    //--------------------------------------------------------------
    // LINES
    
    float breath[3];
    int mappedBreath[3];
    bool fakeBreath;

    vector< Dancer > dancerListOne;
    vector< Dancer > dancerListTwo;
    vector< Dancer > dancerListThree;

    //--------------------------------------------------------------
    // WIFLY
    
    ofxUDPManager udpConnection;
    ofxUDPManager udpConnection2;
    ofxUDPManager udpConnection3;

//    float x,x2,xMapped, xMapped2;
    float x[3];
    float sensorMin[3];// = 1023;
//    float sensorMin2 = 1023;;
    float sensorMax[3];// = 0;
    
    float xMapped[3], oldXmapped[3];
    
    bool calibrating;
//    float sensorMax2 = 0;
    
    //--------------------------------------------------------------
    // OSC
    
    ofxOscReceiver mReceiver;
    
    float pitch[3];
    float amplitude[3];
    float attack[3];
    float FFTavg[3][17];
    
    ofxSyphonServer syphon;
    
    string channel;
    
};

#endif

