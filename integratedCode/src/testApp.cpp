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
}


//--------------------------------------------------------------
void testApp::update(){
    
    getOfc();
    //    updateLines();
   updateOrbitsAndParticles();
    updateWiFly();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofColor _black = 0;
    ofSetColor(_black, 10);
    ofRect(0, 0, ofGetWindowWidth(),ofGetWindowHeight());
    
    //    drawLines();
       drawWiFly();
    drawOrbitsAndParticles();
    
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
void testApp::setupOrbitsAndParticles() {
    
    // Matt adds: clear the vectors on setup (allows restarting).
    particleList.clear();
    setOfOrbits.clear();
    
    for( int i = 0 ; i < 17; i++){
        
        float coe = 1.01 * powf( 1.15, i);
        float _orbit = 30;
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
    
    //mFbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
    
    ofBackground(0);
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::addParticle(float dia){
    cout << "try to add particle" << endl;
    Particle p( pos, vel, acc, _size, dia, particleColor);
    particleList.push_back(p);
    cout << "particle list size = " << particleList.size()  << endl;
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
        
        o->update(xMapped);
    }
    
    
<<<<<<< HEAD
    //----------------------------------FFT STUFF----------------------------------//
=======
    
    for( int i = 0; i < 17;)
    
    for (int i = 0; i < 17; i++){
        
>>>>>>> 141cf61acd2246c8c47145334110642a567d13e7

    
    //This creates more particles according to the volume on each frequency
    for( int i = 0; i < 17; i++){
        
        //cout << "fft band " << i << ": " << FFTavg[0][i] << endl;
        
       if( FFTavg[0][i] > 5){
           cout << "adding particle to fft band " << i << ": " << FFTavg[0][i] << endl;
       addParticle(diameterList[i]);
        }
    }
    
    
    
    
    for (vector < Particle >::iterator it = particleList.begin(); it != particleList.end(); it++) {
                if( it->bIsDead){

                    particleList.erase(it);
        
                };
    };
        for (int i =0; i < 17; i++) {
            speed[i] = ofMap(FFTavg[0][i],0, 24, 0, 10, true);
            rotSpeed[i] = speed[i];
            rotSpeed[i] *= 0.8;
        }
    
    for (vector < Particle >::iterator it = particleList.begin(); it != particleList.end(); it++) {
        for (int i = 0; i<diameterList.size(); i++) {
            if (it->offset == diameterList[i]) {
                it->update(xMapped, rotSpeed[i]);
            };
        };
        
    };
    
//    vector< Particle>::iterator it;
//    int i = 0;
//    for( it = particleList.begin(); it != particleList.end();){
//        
//        if( it->bIsDead){
//            
//            it = particleList.erase(it);
//            
//        }else{
//            
//            speed[i] = ofMap(FFTavg[0][i],0, 24, 0, 10, true);
//            
//            rotSpeed[i] = speed[i];
//            rotSpeed[i] = 10;
//            rotSpeed[i] *= 0.8;
//            //        rotSpeed[i] = fmod(rotSpeed[i], 360);
//            
//            particleList[i].update(xMapped, rotSpeed[i]);
//            
//            it->update(xMapped, rotSpeed[i]);
//            it++;
//            
//        }
//        
//        i++;
//    }
    
    
    //    vector<Particle>::iterator it;
    //    for( it = particleList.begin(); it != particleList.end(); it++){
    //
    //        it->update(xMapped);
    //    }
    
    
    }


//--------------------------------------------------------------
void testApp::drawOrbitsAndParticles(){
    
    //mFbo.begin();
    
    ofClear(255, 255, 255, 0);
    //
//    ofSetColor(0, 0, 0, 20);
//    ofRect(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    
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
<<<<<<< HEAD
    mFbo.end();
    
 
    mFbo.draw(0,0);
    mFbo.draw(-ofGetWindowWidth()/3, 0);
    mFbo.draw(ofGetWindowWidth()/ 3 , 0);
=======
//    mFbo.end();
//    
// 
//    mFbo.draw(0,0);
//    mFbo.draw(-ofGetWindowWidth()/3, 0);
//    mFbo.draw(ofGetWindowWidth()/ 3 , 0);
>>>>>>> 141cf61acd2246c8c47145334110642a567d13e7

    
    

    
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
    
    //Connection 3
    char udpMessage3[100000];
	udpConnection3.Receive(udpMessage3,100000);
	string message3=udpMessage3;
	if(message3!=""){
		//stroke.clear();
		vector<string> strPoints3 = ofSplitString(message3,"[/p]");
        vector<string> point3 = ofSplitString(strPoints3[0],"|");
        if( point3.size() == 1 ){
            x2=atof(point3[0].c_str());
        }
	}
    
    //Connection 1 mapped values
    float pct = 0.1f;
    float oldXMapped = xMapped - 1;
    //Affecting the last two values of the map function determines the output of the breathing in respect to the orbits and particles traveling
    xMapped = ofMap(x, sensorMin, sensorMax, 150, -150);
    xMapped = (1-pct) * oldXMapped + (pct) * xMapped; //thanks charlie!
    
    
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
                cout << "channel value " << i << ": " << FFTavg[0][i] << endl;

            }
            
        }
        
        
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