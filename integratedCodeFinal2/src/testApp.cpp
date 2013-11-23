#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //Let's start some global settings here.
    ofSetVerticalSync(true);
//    ofSetBackgroundAuto(false);
    ofSeedRandom();
    for (int i =0; i<3; i++) {
        cir[i].setup();
        //Set the FFT Channel you want to use
        cir[i].r = i;
        
    }
   
    setupWiFly();
   
    mReceiver.setup(PORT);
    
    syphon.setName("Breath");
    
    for( int i =0; i < 17; i++){
        
        max[i] = 0;
    }
}
//--------------------------------------------------------------
void testApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    getOfc();
    
    for (int i =0; i<3; i++) {
        for( int j = 0; j < 17; j++){
            
            cir[i].max[j] = max[j];
        }
        cir[i].xMapped = xMapped[i];
        cir[i].update(FFTavg);
    }

    updateWiFly();

    for( int i = 0; i < 3; i++){
    breathingData.push_back(x[i]);
    
    if( breathingData.size() > 30){
        
        breathingData.erase( breathingData.begin());
    }
    
    //Averages of the values coming from the sensor
    sum[i] = 0;
    for( int j = 0; j < breathingData.size(); j++){
        
        sum[i] += breathingData[j];
    }
    
    sum[i] = sum[i] /breathingData.size();
    
    newX[i] = sum[i];
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
//    ofColor _black = 0;
//    ofSetColor(_black, 10);
//    ofRect(0, 0, ofGetWindowWidth(),ofGetWindowHeight());
       drawWiFly();

    ofPushMatrix();
    cir[0].draw(0);
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(-ofGetWindowWidth()/3, 0);
    cir[1].draw(1);
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/3, 0);
    cir[2].draw(2);
    ofPopMatrix();

    syphon.publishScreen();
    
    ofSetColor(255);
    ofDrawBitmapString("sensorMin: "+ofToString(sensorMin), 50, 50);
    ofDrawBitmapString("sensorMax: "+ofToString(sensorMax), 50, 75);
    ofDrawBitmapString("xmapped: "+ofToString(xMapped), 50, 100);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key == 'a'){ //boid 1
        x[1] = 815;
        fakeBreath[1] = true;
    } else if(key == 's'){ //boid 0
        x[0] = 815;
        fakeBreath[0] = true;
    } else if(key == 'd'){ //boid 2
        x[2] = 815;
        fakeBreath[2] = true;
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
        }
	} 
    
    for (int i=0; i<3; i++){
        if(fakeBreath[i]){
            if(x[i] > sensorMin[i]){
                //newX[i] = x[i] - 0.5;
                x[i] -= ofRandom(0.1,0.5);
            } else {
                fakeBreath[i] = false;
            }
        }
    }
    
    
    //Sensor values
    //record the maximum sensor value
    for( int i = 0; i < 3; i++){
        if( x[i] > sensorMax[i]){
            sensorMax[i] = x[i];
            //cout << " NeW max val: " << sensorMax << endl;
        }
        
        //record the minium sensor value
        if( x[i] < sensorMin[i] && x[i] > 400) {
            sensorMin[i]  = x[i];
            //cout << " NEW min val: " << sensorMin << endl;
        }
        float pct = 0.05f;
        
        //Affecting the last two values of the map function determines the output of the breathing in respect to the orbits and particles traveling
        //    xMapped[i] = ofMap(newX[i], sensorMin[i], sensorMax[i],150, -75, true);
        xMapped[i] = ofMap(x[i], sensorMin[i], sensorMax[i],150, -75, true);
        xMapped[i] = (1-pct) * oldXMapped[i] + (pct) * xMapped[i]; //thanks charlie!
        oldXMapped[i] = xMapped[i];
        
    }
}

void testApp::drawWiFly() {
    
}
//--------------------------------------------------------------
void testApp::getOfc(){
    
    //OCS
    
    //Hide old messages
    for (int i =0; i < NUMOFSTRINGS; i++){
        if( timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    while( mReceiver.hasWaitingMessages()){
        
        ofxOscMessage m;
        mReceiver.getNextMessage(&m);
        
        if(m.getAddress() == "/Channel01/AudioAnalysis"){
            amplitude[0] = m.getArgAsFloat(0);
            pitch[0] = m.getArgAsFloat(1);
            attack[0] = m.getArgAsFloat(2);
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
        
        if(m.getAddress()=="/Channel01/FFT"){
            Channel01_FFT_size = m.getArgAsInt32(0);
            for( int i = 1; i < 18; i++){
                FFTavg[0][i] = m.getArgAsFloat(i);
                if (FFTavg[0][i-1] > max[i-1]) {
                    max[i-1] = FFTavg[0][i-1];
                }
                max[i-1] = max[i-1]*0.999f;
                //cout << "incomingMax: "<< max[i-1] << endl;
                if ( max[i-1] > 0.0001){
                    FFTavg[0][i-1] = ofMap(FFTavg[0][i-1], 0.f, max[i-1], 0.f, 1.f);
//                cout << "channel value " << i << ": " << max[i-1] << endl;
                }

            }
            
        }
        
        if(m.getAddress()=="/Channel02/FFT"){
            Channel01_FFT_size = m.getArgAsInt32(0);
            for( int i = 1; i < 18; i++){
                FFTavg[1][i] = m.getArgAsFloat(i);
                if (FFTavg[1][i-1] > max[i-1]) {
                    max[i-1] = FFTavg[1][i-1];
                }
                max[i-1] = max[i-1]*0.999f;
                //cout << "incomingMax: "<< max[i-1] << endl;
                if ( max[i-1] > 0.0001){
                    FFTavg[1][i-1] = ofMap(FFTavg[1][i-1], 0.f, max[i-1], 0.f, 1.f);
                    //                cout << "channel value " << i << ": " << max[i-1] << endl;
                }
                
            }
            
        }
        
        if(m.getAddress()=="/Channel03/FFT"){
            Channel01_FFT_size = m.getArgAsInt32(0);
            for( int i = 1; i < 18; i++){
                FFTavg[2][i] = m.getArgAsFloat(i);
                if (FFTavg[2][i-1] > max[i-1]) {
                    max[i-1] = FFTavg[2][i-1];
                }
                max[i-1] = max[i-1]*0.999f;
                //cout << "incomingMax: "<< max[i-1] << endl;
                if ( max[i-1] > 0.0001){
                    FFTavg[2][i-1] = ofMap(FFTavg[2][i-1], 0.f, max[i-1], 0.f, 1.f);
                    //                cout << "channel value " << i << ": " << max[i-1] << endl;
                }
                
            }
            
        }
    }
}