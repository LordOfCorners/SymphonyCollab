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
    mReceiver.setup(12345);
    
        
    fakeBreath = false;
    for(int i=0; i<3; i++){
        sensorMin[i] = 690;
        sensorMax[i] = 810;
        breath[i] = 710;
    }
    calibrating = false;
}


//--------------------------------------------------------------
void testApp::update(){
    

    updateWiFly();
    
    if(calibrating) calibrateWiFly();
    else updateLines();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    while( mReceiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        
        mReceiver.getNextMessage(&m);
        
        if(m.getAddress() == "/Channel01/AudioAnalysis"){
            amplitude[0] = m.getArgAsFloat(0);
            pitch[0] = m.getArgAsFloat(1);
            attack[0] = m.getArgAsFloat(2);
//            cout<< "amplitude chan 1: "<< amplitude[0] << endl;
        }
        
        
        if(m.getAddress() == "/Channel02/AudioAnalysis"){
            amplitude[1] = m.getArgAsFloat(0);
            pitch[1] = m.getArgAsFloat(1);
            attack[1] = m.getArgAsFloat(2);
        }
        
        if(m.getAddress() == "/Channel03/AudioAnalysis"){
            
            amplitude[2] = m.getArgAsFloat(0);
            pitch[2] = m.getArgAsFloat(1);
            attack[2] = m.getArgAsFloat(2);
        }
        
        if(m.getAddress() == "/Channel01/FFT"){
            for (int i=0; i<17; i++){
                //FFTavg[0][i] = m.getArgAsFloat(i);
            }
        }
        
        if(m.getAddress() == "/Channel02/FFT"){
            for (int i=0; i<17; i++){
                //FFTavg[1][i] = m.getArgAsFloat(i);
            }
        }
        
        if(m.getAddress() == "/Channel03/FFT"){
            for (int i=0; i<17; i++){
               // FFTavg[2][i] = m.getArgAsFloat(i);
//                cout<< i << ": "<< FFTavg[2][i] << endl;
            }
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    

    
    if(calibrating){
        ofSetColor(255);
        ofDrawBitmapString("calibrating", 100,100);
        
    } else {
        ofSetColor(0,0,0, 2);
        ofRect( 0,0, ofGetWindowWidth(), ofGetWindowHeight() );
        drawLines();
    }
    
    syphon.publishScreen();
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
//        case '2':
//            if ( key == '2' ) {
//                noiseBreath = !noiseBreath;
//            }
//            break;
        case 'b':
            fakeBreath = true;
            breath[0] = 800;
            breath[1] = 800;
            breath[2] = 800;
            
            break;
        case 'c':
            //calibrateWiFly();
            calibrating = !calibrating;
            break;
    } 
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
    
//    breath = 0;
//    breathRad = 50;
    //noiseBreath = true;
    
    // Create Dancers, feed in a pos and vel, and add them to the vector.
    for ( int i = 0; i < NUMDANCERSONE; i++ ) {
        Dancer instrumentOne( ofVec2f( (ofGetScreenWidth()/2)-300, 540 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ), 1 );
        dancerListOne.push_back( instrumentOne );
    }
    
    for ( int i = 0; i < NUMDANCERSTWO; i++ ) {
        Dancer instrumentTwo( ofVec2f( ofGetScreenWidth()/2, 540 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ), 2 );
        dancerListThree.push_back( instrumentTwo );
    }
    
    for ( int i = 0; i < NUMDANCERSTHREE; i++ ) {
        Dancer instrumentThree( ofVec2f( (ofGetScreenWidth()/2)+300, 540 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ), 3 );
        dancerListThree.push_back( instrumentThree );
    }
}

//--------------------------------------------------------------
void testApp::updateLines() {
    
    // When we have real breathing data we won't need this, but for the time being, let's fake it.
//    float waveSpeed = 1;
//    if ( !noiseBreath ) {
//        breath = sin( ofGetElapsedTimef() * waveSpeed) * breathRad;
//    } else {
//        breath = ofNoise( sin( ofGetElapsedTimef() * waveSpeed ) ) * breathRad;
//        cout<<breath<<endl;
//    }
//
  
    if(fakeBreath){
        for (int i=0; i<3; i++){
            if (breath[i] > 700){
                breath[i] -= 0.3;
            } else {
                fakeBreath = false;
            }
        }
    }
    //cout << "original breath: "<<breath[0] <<endl;

    for(int i=0; i<3; i++){
        
        amplitude[i] = amplitude[i] * 10 + 1; // map amplitude to 0 - 50
        mappedBreath[i] = ofMap(breath[i], sensorMin[i], sensorMax[i], 25.0f, 100.0f); //map breath to 0.1, -0.1
    }
    
    // Pass in the data and update the Dancers.
    for ( int i = 0; i < dancerListOne.size(); i++ ) {
        dancerListOne[ i ].update( mappedBreath[0], amplitude[0] );
    }
    
    for ( int i = 0; i < dancerListTwo.size(); i++ ) {
        dancerListTwo[ i ].update( mappedBreath[1], amplitude[1] );
    }
    
    for ( int i = 0; i < dancerListThree.size(); i++ ) {
        dancerListThree[ i ].update( mappedBreath[2], amplitude[2]);
    }
    
    // check size
//    cout << "listone.size: "<< dancerListOne.size() << endl;
//    if (dancerListOne.size() > 500){
//        dancerListOne.pop_back();
//    }
//    if (dancerListTwo.size() > 500){
//        dancerListTwo.pop_back();
//    }
//    if (dancerListThree.size() > 500){
//        dancerListThree.pop_back();
//    }
    

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
    
    //create the socket and bind to port 11999
    udpConnection3.Create();
    udpConnection3.Bind(11999);
    udpConnection3.SetNonBlocking(true);
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
            x[0]=atof(point[0].c_str());
            breath[0] = x[0];
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
            x[1]=atof(point2[0].c_str());
            breath[1] = x[1];
        }
	}
    
    //Connection 3
    char udpMessage3[100000];
	udpConnection3.Receive(udpMessage3,100000);
	string message3=udpMessage3;
	if(message3!=""){
		//stroke.clear();
		vector<string> strPoints3 = ofSplitString(message3,"[/p]");
        vector<string> point3 = ofSplitString(strPoints3[0],"|");
        if( point3.size() == 1 ){
            x[2]=atof(point3[0].c_str());
            breath[2] = x[2];
        }
	}
    
    //Connection 1 mapped values
//    float pct = 0.1f;
//    float oldXMapped = xMapped - 1;
    //Affecting the last two values of the map function determines the output of the breathing in respect to the orbits and particles traveling
    
    //    xMapped2 = ofMap(x2, sensorMin2, sensorMax2, 255, 0);
    
    //    cout << x << " | " << sensorMin << " | " << sensorMax <<  " | " << xMapped << endl;
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
    for (int i=0; i<3; i++){
        if( x[i] > sensorMax[i]){
            sensorMax[i] = x[i];
        }
        
        //record the minium sensor value
        if( x[i] < sensorMin[i]) {
            sensorMin[i]  = x[i];
        }
    }
}


