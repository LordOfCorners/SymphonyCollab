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
    
    syphon.setName("Breath_Release");
    
    fakeBreath = false;
    for(int i=0; i<3; i++){
        sensorMin[i] = 1000;
        sensorMax[i] = 400;
        breath[i] = 500;
    }
    calibrating = false;
}


//--------------------------------------------------------------
void testApp::update(){
    

    updateWiFly();
    calibrateWiFly();
    updateLines();
    
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
//    
//    for( int i = 0; i < 3; i++){
//        
//        breath[i] = xMapped[i];
//    }
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
    
    ofSetColor(255);

    string thisMsg = ofToString(sensorMax[0]);
    ofDrawBitmapString("sensorMax 1: "+thisMsg, 300, 50);
    thisMsg = ofToString(sensorMin[0]);
    ofDrawBitmapString("sensorMin 1: "+thisMsg, 300, 75);
    thisMsg = ofToString(amplitude[0]);
    ofDrawBitmapString("amplitude 1: "+thisMsg, 300, 100);
    thisMsg = ofToString(breath[0]);
    ofDrawBitmapString("breath 1: "+thisMsg, 300, 125);
    
    thisMsg = ofToString(sensorMax[1]);
    ofDrawBitmapString("sensorMax 2: "+thisMsg, 600, 50);
    thisMsg = ofToString(sensorMin[1]);
    ofDrawBitmapString("sensorMin 2: "+thisMsg, 600, 75);
    thisMsg = ofToString(amplitude[1]);
    ofDrawBitmapString("amplitude 2: "+thisMsg, 600, 100);
    thisMsg = ofToString(breath[1]);
    ofDrawBitmapString("breath 2: "+thisMsg, 600, 125);
    
    
    thisMsg = ofToString(sensorMax[2]);
    ofDrawBitmapString("sensorMax 3: "+thisMsg, 900, 50);
    thisMsg = ofToString(sensorMin[2]);
    ofDrawBitmapString("sensorMin 3: "+thisMsg, 900, 75);
    thisMsg = ofToString(amplitude[2]);
    ofDrawBitmapString("amplitude 3: "+thisMsg, 900, 100);
    thisMsg = ofToString(breath[2]);
    ofDrawBitmapString("breath 3: "+thisMsg, 900, 125);
    

    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch ( key ) {
// Reset everything with 'r' (debug).
        case 'r':
        case 'R':
            setup();
            break;

        case '1':
            for ( int i = 0; i < dancerListOne.size(); i++ ){
                dancerListOne[ i ].fillIn = !dancerListOne[ i ].fillIn;
            }
            break;
 
        case 'a':
            fakeBreath = true;
            breath[0] = 1600;
            break;
            
        case 's':
            fakeBreath = true;
            breath[1] = 1600;
            break;
            
        case 'd':
            fakeBreath = true;
            breath[2] = 1600;
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
    dancerListTwo.clear();
    
    for ( int i = 0; i < dancerListThree.size(); i++) {
        dancerListThree[ i ].lineList.clear();
    }
    dancerListThree.clear();
    
    // Create Dancers, feed in a pos and vel, and add them to the vector.
    for ( int i = 0; i < NUMDANCERSONE; i++ ) {
        Dancer instrumentOne( ofVec2f( (ofGetWidth()/2)-600, 700 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ), 1 );
        dancerListOne.push_back( instrumentOne );
    }
    
    for ( int i = 0; i < NUMDANCERSTWO; i++ ) {
        Dancer instrumentTwo( ofVec2f( ofGetWidth()/2+75, 600 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ), 2 );
        dancerListTwo.push_back( instrumentTwo );
    }
    
    for ( int i = 0; i < NUMDANCERSTHREE; i++ ) {
        Dancer instrumentThree( ofVec2f( (ofGetWidth()/2)+700, 640 ),  ofVec2f( ofRandom( -5, 5 ), ofRandom( -0.5, 0.5 ) ), 3 );
        dancerListThree.push_back( instrumentThree );
    }
}

//--------------------------------------------------------------
void testApp::updateLines() {
  
    if(fakeBreath){
        for (int i=0; i<3; i++){
            if (breath[i] > 1200){
                breath[i] -= 0.3;
            } else {
                fakeBreath = false;
            }
        }
    }
    //cout << "original breath: "<<breath[0] <<endl;

    for(int i=0; i<3; i++){
        
        amplitude[i] = amplitude[i] * 10 + 1; // map amplitude to 0 - 50
//        cout<<"breath to map: "<< breath[i]<<endl;
//        cout<<"sensorMin: "<< sensorMin[i]<<endl;
        mappedBreath[i] = ofMap(breath[i], sensorMin[i], sensorMax[i], 0, 100); //map breath to 0.1, -0.1
       
    }
//     cout << "BREATH MAPPED :"<<mappedBreath[0]<<endl;
    
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
//        cout << "MESSAGE: "<<message << endl;
		vector<string> strPoints = ofSplitString(message,"[/p]");
        vector<string> point = ofSplitString(strPoints[0],"|");
        if( point.size() == 1 ){
            x[0]=atof(point[0].c_str());
            breath[0] = x[0];
            //cout << "MESSAGE1: "<<breath[0] << endl;
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
            //cout << "MESSAGE2: "<< breath[1] << endl;
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
            //cout << "MESSAGE3: "<<breath[2] << endl;
        }
	}
    
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
        if( x[i] < sensorMin[i] && x[i] > 400) {
            sensorMin[i]  = x[i];
        }
    }
}


