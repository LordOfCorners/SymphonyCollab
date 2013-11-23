#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //Let's start some global settings here.
    ofSetVerticalSync(true);
    ofSeedRandom();
//    ofBackground(0);
//    ofSetBackgroundAuto(false);
    
	
   
    setupWiFly();
    //    setupLines();
    setupOrbitsAndParticles();
    
    
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
    //    updateLines();
   updateOrbitsAndParticles();
    updateWiFly();
    

    for( int i = 0; i < 3; i++){
    breathingData.push_back(x[i]);
    
    if( breathingData.size() > 30){
        
        breathingData.erase( breathingData.begin());
    }
    
    
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
    
    ofColor _black = 0;
    ofSetColor(_black, 10);
    ofRect(0, 0, ofGetWindowWidth(),ofGetWindowHeight());
       drawWiFly();
    drawOrbitsAndParticles();
    
    syphon.publishScreen();
    
    ofSetColor(255);
    ofDrawBitmapString("sensorMin: "+ofToString(sensorMin), 50, 50);
    ofDrawBitmapString("sensorMax: "+ofToString(sensorMax), 50, 75);
    ofDrawBitmapString("xmapped: "+ofToString(xMapped), 50, 100);
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch ( key ) {
            // Reset everything with 'r' (debug).
        case 'r':
        case 'R':
            setup();
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
void testApp::setupOrbitsAndParticles() {
    
    // Matt adds: clear the vectors on setup (allows restarting).
    particleList.clear();
    setOfOrbits.clear();
    
    
    
    for( int i = 0 ; i < 17; i++){
        
        
        float coe = 1.01 * powf( 1.15, i);
        float _orbit = 25;
        diameterList.push_back( _orbit * coe);
        
    }
    
    //    acc.set(0);
    
    for( int i = 0; i < 17; i++){
        
        _size = ofRandom(2, 5);
        pos.set(ofRandom(ofGetWindowWidth() / 2), ofRandom(ofGetWindowHeight()));
        vel.set(ofRandom(.9));
        particleColor.setHsb(ofRandom(255), 255, 255);
        
        addOrbit(diameterList[i]);
        addParticle(diameterList[i]);
        
        
    }
    
    mFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    
    ofBackground(0);
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::addParticle(float dia){
//    cout << "try to add particle" << endl;
    Particle p( pos, vel, acc, _size, dia, particleColor);
    particleList.push_back(p);
//    cout << "particle list size = " << particleList.size()  << endl;
    //    rotDia = setOfOrbits[i].dia;

}

//--------------------------------------------------------------
void testApp::addOrbit(float dia){
    
    Orbit tmp( ofPoint( ofGetWindowWidth()/2, ofGetWindowHeight()/ 2), dia);
    setOfOrbits.push_back( tmp);
    
    
}

//--------------------------------------------------------------
void testApp::updateOrbitsAndParticles() {
    
    vector<Orbit>::iterator o;
    for( o = setOfOrbits.begin(); o != setOfOrbits.end(); o++){
        
        o->update(xMapped[0]);
    }
    
    
    //----------------------------------FFT STUFF----------------------------------//

    
    //This creates more particles according to the volume on each frequency
    for( int i = 0; i < 17; i++){
        
        //cout << "fft band " << i << ": " << FFTavg[0][i] << endl;
        
       if( FFTavg[0][i] > 0.9f){
//           cout << "adding particle to fft band " << i << ": " << FFTavg[0][i];
       addParticle(diameterList[i]);
        }
    }
    
    
    for (int i =0; i < 17; i++){
        speed[i] = ofMap(FFTavg[0][i],0, 24, 0, 10, true);
        rotSpeed[i] = speed[i];
        rotSpeed[i] *= 0.8;
    }
    
    for (vector < Particle >::iterator it = particleList.begin(); it != particleList.end();) {
        
        if( it->bIsDead){

            particleList.erase(it);

        }else{
            
            for (int i = 0; i<diameterList.size(); i++) {
                if (it->offset == diameterList[i]) {
                    it->update(xMapped[0], rotSpeed[i]);
                };
            };
            
            it++;
        }
    }
}


//--------------------------------------------------------------
void testApp::drawOrbitsAndParticles(){
    
    mFbo.begin();
    
//    ofClear(255, 255, 255, 0);
    //
    ofSetColor(0, 0, 0, 20);
    ofRect(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    
    vector<Orbit>::iterator p;
    for( p = setOfOrbits.begin(); p != setOfOrbits.end(); p++){
        
        p->draw();
    }
    
    
    vector<Particle>::iterator it;
    int i = 0;
    for( it = particleList.begin(); it != particleList.end(); it++){
        
        it->draw();
//        ofDrawBitmapString(ofToString(rotSpeed[i]), 180, i * 20);
        
        //This index goes at the end so that when it loops for the first time it takes 0 as a value and not one
        i++;
    
    }
    mFbo.end();
    
 
    mFbo.draw(0,0);
    mFbo.draw(-ofGetWindowWidth()/3, 0);
    mFbo.draw(ofGetWindowWidth()/ 3 , 0);
  
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
    
    
    //Sensor 1
    //record the maximum sensor value
    
    for( int i = 0; i < 3; i++){
    if( x[i] > sensorMax[i]){
        sensorMax[i] = x[i];
        //cout << " NEW max val: " << sensorMax << endl;
    }
    
    //record the minium sensor value
    if( x[i] < sensorMin[i] && x[i] > 400) {
        sensorMin[i]  = x[i];
        //cout << " NEW min val: " << sensorMin << endl;
    }
    
    //Connection 1 mapped values
    float pct = 0.05f;
    
    //Affecting the last two values of the map function determines the output of the breathing in respect to the orbits and particles traveling
//    cout << " sensorMin: " << sensorMin << endl;
//    cout << " sensorMax: " << sensorMax << endl;
    
    xMapped[i] = ofMap(newX[i], sensorMin[i], sensorMax[i],150, -75, true);
    xMapped[i] = (1-pct) * oldXMapped[i] + (pct) * xMapped[i]; //thanks charlie!
    oldXMapped[i] = xMapped[i];
        
    }
    
    cout << " values of x: " << x << endl;
    
    
    
    
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
//    if( x > sensorMax){
//        sensorMax = x;
//    }
//    
//    //record the minium sensor value
//    if( x < sensorMin) {
//        sensorMin  = x;
//    }
//    
//    //Sensor 2
//    //record the maximum sensor value
//    if( x2 > sensorMax2){
//        sensorMax2 = x2;
//    }
//    
//    //record the minium sensor value
//    if( x2 < sensorMin2) {
//        sensorMin2  = x2;
//    }
    //    }
}

void testApp::getOfc(){
    
    //OCS
    
    //Hide old messages
//    for (int i =0; i < NUMOFSTRINGS; i++){
//        if( timers[i] < ofGetElapsedTimef()){
//            msg_strings[i] = "";
//        }
//    }
    
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
        
        //FFT values
//        if(m.getAddress() == "/Channel01/FFT"){
//            for (int i=0; i<17; i++){
//                if( i < 1){
//                    FFTavg[0][i] = m.getArgAsInt32(i);
//                } else {
//                    FFTavg[0][i] = m.getArgAsFloat(i);
//                }
//                cout << "channel value " << i << ": " << FFTavg[0][i] << endl;
//            }
//        }
        
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
        
        
//        if(m.getAddress()=="/Channel01/FFT"){
//            Channel01_FFT_size = m.getArgAsInt32(0);
//            for( int i = 1; i < 18; i++){
//                FFTavg[0][i] = m.getArgAsFloat(i);
//                if (FFTavg[0][i+1] > max[i]) {
//                    max[i] = FFTavg[0][i+1];
//                }
//                max[i+1] = max[i-1]*0.999f;
//                cout << "incomingMax: "<< max[i] << endl;
//                FFTavg[0][i+1] = ofMap(FFTavg[0][i+1], 0.f, max[i], 0.f, 1.f);
//                //                cout << "channel value " << i << ": " << max[i-1] << endl;
//                
//            }
//            
//        }
        
//        if(m.getAddress()=="/Channel01/FFT"){
//            Channel01_FFT_size = m.getArgAsInt32(0);
//            for( int i = 1; i < 18; i++){
//                FFTavg[0][i] = m.getArgAsFloat(i);
//            }
//            
//        }

        
        
        if(m.getAddress() == "/Channel02/FFT"){
            for (int i=0; i<17; i++){
                //FFTavg[1][i] = m.getArgAsFloat(i);
            }
        }
        
        if(m.getAddress() == "/Channel03/FFT"){
            for (int i=0; i<17; i++){
                //FFTavg[2][i] = m.getArgAsFloat(i);
                //                cout<< i << ": "<< FFTavg[2][i] << endl;
            }
            
            
        }
        
    }
    
    
}