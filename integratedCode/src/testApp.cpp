#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
    setupFFT();
    //    setupLines();
}


//--------------------------------------------------------------
void testApp::update(){
    
    //    updateFFT();
    updateLines();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //    drawFFT();
    drawLines();
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch ( key ) {
            // Reset everything with 'r' (debug).
        case 'r':
        case 'R':
            setup();
            break;
            
            //-------------LINES-------------
            
            // Toggle "fillIn" mode on and off.
        case '1':
            for ( int i = 0; i < dancerList.size(); i++ ){
                dancerList[ i ].fillIn = !dancerList[ i ].fillIn;
            }
            break;
            // Toggle "noiseBreath" mode on and off.
        case '2':
            if ( key == '2' ) {
                noiseBreath = !noiseBreath;
            }
            break;
    } // END SWITCH
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
    
}

//--------------------------------------------------------------
void testApp::setupLines() {
    
    // First of all, clear out the vectors (in case of reset).
    // First the lineLists inside the dancerList...
    for ( int i = 0; i < dancerList.size(); i++) {
        dancerList[ i ].lineList.clear();
    }
    // ...then the dancerList itself.
    dancerList.clear();
    
    // Maintenance
    ofSetVerticalSync( true );
    ofSetFrameRate( 60 );
    ofSetCircleResolution( 100 );
    
    // May want to change this to a gradient or something else.
    ofBackground( 0 );
    
    breath = 0;
    breathRad = 50;
    noiseBreath = true;
    
    // Create Dancers, feed in a pos and vel, and add them to the vector.
    for ( int i = 0; i < NUMDANCERS; i++ ) {
        Dancer instrument( ofVec2f( ofRandomWidth(), ofRandomHeight() ),  ofVec2f( ofRandom( -0.5, 0.5 ), ofRandom( -0.5, 0.5 ) ) );
        dancerList.push_back( instrument );
    }
}

//--------------------------------------------------------------
void testApp::updateLines() {
    
    // Set the color back to default.
    dancerList[ 0 ].c.set( ofColor( 255, 0, 0 ) );
    dancerList[ 1 ].c.set( ofColor( 0, 255, 0 ) );
    dancerList[ 2 ].c.set( ofColor( 0, 0, 255 ) );
    
    // Change the color upon collision. This isn't working right now and it also makes the app run really slowly, so I'm turning it off.
    /*for ( int i = 0; i < dancerList.size(); i++ ) {
     for ( int j = 0; j < dancerList.size(); j++ ) {
     for ( int k = 0; k < dancerList[ i ].lineList.size(); k++ ) {
     for ( int l = 0; l < dancerList[ j ].lineList.size(); l++ ) {
     if ( dancerList[ i ].lineList[ k ].pos == dancerList[ j ].lineList[ l ].pos ) {
     dancerList[ i ].lineList[ k ].c = ofColor(255);
     dancerList[ j ].lineList[ l ].c = ofColor(255);
     }
     }
     }
     }
     }*/
    
    // When we have real breathing data we won't need this, but for the time being, let's fake it.
    float waveSpeed = 1;
    if ( !noiseBreath ) {
        breath = sin( ofGetElapsedTimef() * waveSpeed ) * breathRad;
    } else {
        breath = ofNoise( sin( ofGetElapsedTimef() * waveSpeed ) ) * breathRad;
    }
    
    // Pass in the data and update the Dancers.
    for ( int i = 0; i < dancerList.size(); i++ ) {
        dancerList[ i ].update( breath );
    }
}

//--------------------------------------------------------------
void testApp::drawLines() {
    
    for ( int i = 0; i < dancerList.size(); i++ ) {
        dancerList[ i ].draw();
    }
}

//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
}

//--------------------------------------------------------------
void testApp::setupFFT() {
    
    // 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)
	
	ofSoundStreamSetup(0,2,this, 44100, BUFFER_SIZE, 4);
	
	//left = new float[BUFFER_SIZE];
	//right = new float[BUFFER_SIZE];
    
	ofSetHexColor(0x666666);
	
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	
	FFTanalyzer.peakHoldTime = 15; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = 0.01f; // increasing gain at higher frequencies
	
	ofSetVerticalSync(true);
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void testApp::updateFFT() {
    
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::drawFFT() {
    
    float avg_power = 0.0f;
    
	/* do the FFT	*/
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freq[i] = magnitude[i];
	}
	
	FFTanalyzer.calculate(freq);
	
	float bandWidth = ofGetWidth() / FFTanalyzer.nAverages;
	
	ofSetHexColor(0xffffff);
	//for (int i = 0; i < (int)(BUFFER_SIZE/2 - 1); i++){
	//ofRect(200+(i*4),600,4,-freq[i]*10.0f);
	//}
    
	for (int i = 0; i < FFTanalyzer.nAverages; i++){
		
		// Add some amount of spin based on the volume, but decrease it over
		// time by scaling it down 15%
		// make sure it doesn't go below 0
		spin[i] += ofMap(FFTanalyzer.averages[i] * 0.005, 0, 0.2, 0, 8);
		spin[i] *= 0.8;
		spin[i] = fmax(spin[i], 0);
		
		// increase our current angle by the amount of spin
		// wrap around 360 so our angle var doesn't get huge
		theta[i] += spin[i];
		theta[i] = fmod(theta[i], 360);
        
		ofPushMatrix();
		ofTranslate(bandWidth * i, ofGetHeight() / 2);
		ofRotateZ(theta[i]);
        //		ofRect(bandWidth * i, 600, bandWidth, -FFTanalyzer.averages[i] * 6);
		ofRect(0, 0, bandWidth * 2, FFTanalyzer.averages[i]);
		
        //		for (int j = 0; j < 4; j ++) {
        //			ofPushMatrix();
        //			ofTranslate(sin(ofGetElapsedTimef() * (j+1))*50, cos(ofGetElapsedTimef() * (j+1))*50);
        //			ofRotateX(ofGetElapsedTimef()*2);
        //			ofRect(0, 0, 5, 3);
        //			ofPopMatrix();
        //		}
		
		ofPopMatrix();
        
	}
	
	ofSetHexColor(0xff0000);
	for (int i = 0; i < FFTanalyzer.nAverages; i++){
		//ofRect(bandWidth * i,600-FFTanalyzer.peaks[i] * 6, bandWidth,-4);
	}
}