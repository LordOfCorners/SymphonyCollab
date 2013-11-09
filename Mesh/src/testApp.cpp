#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
  	
    setupLines();
    ofSetVerticalSync( true );
    ofSetFrameRate(30);
    ofSeedRandom();
    ofBackground(0);
    ofSetBackgroundAuto(true);
    
    setupWiFly();
}


//--------------------------------------------------------------
void testApp::update(){
    
    updateLines();
    updateWiFly();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(0,0,0, 2);
    ofRect( 0,0, ofGetWindowWidth(), ofGetWindowHeight() );
    drawLines();
    
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
            for ( int i = 0; i < dancerListOne.size(); i++ ){
                dancerListOne[ i ].fillIn = !dancerListOne[ i ].fillIn;
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

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
    
}

//--------------------------------------------------------------
void testApp::setupLines() {
    
    for ( int i = 0; i < dancerListOne.size(); i++) {
        dancerListOne[ i ].lineList.clear();
    }
    dancerListOne.clear();
    
    for ( int i = 0; i < dancerListTwo.size(); i++) {
        dancerListTwo[ i ].lineList.clear();
    }
    dancerListOne.clear();
    
    for ( int i = 0; i < dancerListThree.size(); i++) {
        dancerListThree[ i ].lineList.clear();
    }
    dancerListOne.clear();
    
//    ofSetCircleResolution(100);
    
    // May want to change this to a gradient or something else.
    //    ofBackground( 0 );
    
    breath = 0;
    breathRad = 50;
    noiseBreath = true;
    
    // Create Dancers, feed in a pos and vel, and add them to the vector.
    for ( int i = 0; i < NUMDANCERSONE; i++ ) {
        Dancer instrumentOne( ofVec2f( (ofGetScreenWidth()/2)-300, 540 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ) );
        dancerListOne.push_back( instrumentOne );
    }
    
    for ( int i = 0; i < NUMDANCERSTWO; i++ ) {
        Dancer instrumentTwo( ofVec2f( ofGetScreenWidth()/2, 540 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ) );
        dancerListThree.push_back( instrumentTwo );
    }
    
    for ( int i = 0; i < NUMDANCERSTHREE; i++ ) {
        Dancer instrumentThree( ofVec2f( (ofGetScreenWidth()/2)+300, 540 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ) );
        dancerListThree.push_back( instrumentThree );
    }
}

//--------------------------------------------------------------
void testApp::updateLines() {
    
    // When we have real breathing data we won't need this, but for the time being, let's fake it.
    float waveSpeed = 1;
    if ( !noiseBreath ) {
        breath = sin( ofGetElapsedTimef() * waveSpeed) * breathRad;
    } else {
        breath = ofNoise( sin( ofGetElapsedTimef() * waveSpeed ) ) * breathRad;
    }
    
    // Pass in the data and update the Dancers.
    for ( int i = 0; i < dancerListOne.size(); i++ ) {
        dancerListOne[ i ].update( breath );
    }
    
    for ( int i = 0; i < dancerListTwo.size(); i++ ) {
        dancerListTwo[ i ].update( breath );
    }
    
    for ( int i = 0; i < dancerListThree.size(); i++ ) {
        dancerListThree[ i ].update( breath );
    }
}

//--------------------------------------------------------------
void testApp::drawLines() {
    
    //    ofSetColor(0,0,0, 255*0.03);
    //    ofRect( ofGetWindowRect() );
    
    for ( int i = 0; i < dancerListOne.size(); i++ ) {
        dancerListOne[ i ].draw();
    }
    
    for ( int i = 0; i < dancerListTwo.size(); i++ ) {
        dancerListTwo[ i ].draw();
    }
    
    for ( int i = 0; i < dancerListThree.size(); i++ ) {
        dancerListThree[ i ].draw();
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


