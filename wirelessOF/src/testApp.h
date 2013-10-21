#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofxUDPManager udpConnection;
		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;

		vector<ofPoint> stroke;
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    int zmin;
    int zmax;
    int mxmin;
    int mxmax;
    int mymin;
    int mymax;
    int mzmin;
    int mzmax;
};

