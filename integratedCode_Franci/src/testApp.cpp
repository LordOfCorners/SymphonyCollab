#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  	
    //    setupFFT();
        setupLines();
//        setupOrbitsAndParticles();
    //Let's start some global settings here.
    ofSetVerticalSync(true);
    ofSeedRandom();
    ofBackground(0);
    ofSetBackgroundAuto(false);
    
    setupWiFly();
}


//--------------------------------------------------------------
void testApp::update(){
    
    //    updateFFT();
        updateLines();
//        updateOrbitsAndParticles();
    updateWiFly();
   
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(0,0,0, 2);
    ofRect( 0,0, ofGetWindowWidth(), ofGetWindowHeight() );
    
    //    drawFFT();
        drawLines();
//        drawOrbitsAndParticles();
//      drawWiFly();
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
        case 'c':
        case 'C':
            calibrateWiFly();
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
	
    //-------------ORBITS-------------
    
//    for( int i = 0; i < diameterList.size() ; i++){
//        
//        if ( ofRandom( 1 ) < 0.01 ) {
//            
//            if ( /* music is high frequency*/ ) {
//                i = 12;
//            }
//            else if ( /* music is low frequency */) {
//                i = 2;
//            }
//            
//            addParticle( i );
//        }
//    }
    
    addParticle(diameterList[4]);
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
    //Mauricio: The first two need to be added in the main setup.
//    ofSetVerticalSync( true );
//    ofSetFrameRate(60);
    ofSetCircleResolution(100);
    
    // May want to change this to a gradient or something else.
//    ofBackground( 0 );
    
    breath = 0;
    breathRad = 50;
    noiseBreath = true;
    
    // Create Dancers, feed in a pos and vel, and add them to the vector.
    for ( int i = 0; i < NUMDANCERS; i++ ) {
        Dancer instrument( ofVec2f( ofRandomWidth(), ofRandomHeight()),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ) );
        dancerList.push_back( instrument );
    }
}

//--------------------------------------------------------------
void testApp::updateLines() {
    
    // Set the color back to default.
//    dancerList[ 0 ].c.set( ofColor( 255, 0, 0 ) );
//    dancerList[ 1 ].c.set( ofColor( 0, 255, 0 ) );
//    dancerList[ 2 ].c.set( ofColor( 0, 0, 255 ) );
    
    
    
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
        breath = sin( ofGetElapsedTimef() * waveSpeed) * breathRad;
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
    
//    ofSetColor(0,0,0, 255*0.03);
//    ofRect( ofGetWindowRect() );
    
    for ( int i = 0; i < dancerList.size(); i++ ) {
        dancerList[ i ].draw();
    }
}

//--------------------------------------------------------------
void testApp::setupOrbitsAndParticles() {
    
    // Matt adds: clear the vectors on setup (allows restarting).
    particleList.clear();
    setOfOrbits.clear();
    
    for( int i = 0 ; i < 17; i++){
        
        float coe = 1.02 * powf( 1.19, i);
        float _orbit = 40;
        diameterList.push_back( _orbit * coe);
        
    }
    
    //    acc.set(0);
    
    for( int i = 0; i < 17; i++){
        
        _size = ofRandom(2, 5);
        pos.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()));
        vel.set(ofRandom(0,.9));
        
        
        addOrbit(diameterList[i]);
        addParticle(diameterList[i]);
        
        
    }
}

//--------------------------------------------------------------
void testApp::addParticle(float dia){
    
    Particle p( pos, vel, acc, _size, dia, particleColor);
    particleList.push_back(p);
    
    //    rotDia = setOfOrbits[i].dia;
}

//--------------------------------------------------------------
void testApp::addOrbit(float dia){
    
    Orbit tmp( ofPoint( ofGetWindowWidth()/2, ofGetWindowHeight ()), dia);
    setOfOrbits.push_back( tmp);
    
    
}

//--------------------------------------------------------------
void testApp::updateOrbitsAndParticles() {
    
    vector<Orbit>::iterator o;
    for( o = setOfOrbits.begin(); o != setOfOrbits.end(); o++){
        
        o->update(xMapped);
    }
    
    vector<Particle>::iterator it;
    for( it = particleList.begin(); it != particleList.end(); it++){
     
        it->update(xMapped);
    }
   
    
 
}

//--------------------------------------------------------------
void testApp::drawOrbitsAndParticles(){
    
    
    vector<Orbit>::iterator p;
    for( p = setOfOrbits.begin(); p != setOfOrbits.end(); p++){
        
        p->draw();
        
   
    }
    
    vector<Particle>::iterator it;
    for( it = particleList.begin(); it != particleList.end(); it++){
        
        it->draw();
    }

}

//--------------------------------------------------------------
void testApp::setupWiFly() {
    
    //create the socket and bind to port 11997
    udpConnection.Create();
    udpConnection.Bind(11997);
    udpConnection.SetNonBlocking(true);
    
    //create the socket and bind to port 11998
    udpConnection2.Create();
    udpConnection2.Bind(11998);
    udpConnection2.SetNonBlocking(true);
    }

//--------------------------------------------------------------
void testApp::updateWiFly() {
    
    //Connection 1
	char udpMessage[100000];
	udpConnection.Receive(udpMessage,100000);
	string message=udpMessage;
	if(message!=""){
		vector<string> strPoints = ofSplitString(message,"[/p]");
        vector<string> point = ofSplitString(strPoints[0],"|");
        if( point.size() == 1 ){
            x=atof(point[0].c_str());
        }
	}
    
    //Connection 2
    char udpMessage2[100000];
	udpConnection2.Receive(udpMessage2,100000);
	string message2=udpMessage2;
	if(message2!=""){
		//stroke.clear();
		vector<string> strPoints2 = ofSplitString(message2,"[/p]");
        vector<string> point2 = ofSplitString(strPoints2[0],"|");
        if( point2.size() == 1 ){
            x2=atof(point2[0].c_str());
        }
	}
    float pct = 0.1f;
    float oldXMapped = xMapped - 1;
    //Affecting the last two values of the map function determines the output of the breathing in respect to the orbits and particles traveling
    xMapped = ofMap(x, sensorMin, sensorMax, 100, 0);
    xMapped = (1-pct) * oldXMapped + (pct) * xMapped; //thanks charlie!

    
    //    xMapped2 = ofMap(x2, sensorMin2, sensorMax2, 255, 0);
    
    cout << x << " | " << sensorMin << " | " << sensorMax <<  " | " << xMapped << endl;
//    calibrateWiFly();

}

//--------------------------------------------------------------
void testApp::drawWiFly() {
    
    //
}

//--------------------------------------------------------------
void testApp::calibrateWiFly() {
    
    //Calibration
    //Calibrate for first 5 seconds
//    if (ofGetElapsedTimef() >1 && ofGetElapsedTimef() < 12){
    
        //Sensor 1
        //record the maximum sensor value
        if( x > sensorMax){
            sensorMax = x;
        }
        
        //record the minium sensor value
        if( x < sensorMin) {
            sensorMin  = x;
        }
        
        //Sensor 2
        //record the maximum sensor value
        if( x2 > sensorMax2){
            sensorMax2 = x2;
        }
        
        //record the minium sensor value
        if( x2 < sensorMin2) {
            sensorMin2  = x2;
        }
//    }
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
    
//	ofSetHexColor(0x666666);
	
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	
	FFTanalyzer.peakHoldTime = 15; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = 0.01f; // increasing gain at higher frequencies
	
	
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void testApp::updateFFT() {
    
//    ofBackground(0);
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
	
//	ofSetHexColor(0xffffff);
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