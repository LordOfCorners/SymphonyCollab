#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "Orbit.h"

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
//Use this to add random particles in different orbits
//        void addParticle( int i );
        void addParticle(float dia);
        void addOrbit(float dia);
    
    
    vector < Particle > particleList;
    vector < Orbit > setOfOrbits;
    vector < float > diameterList;
    
    ofVec2f pos , vel, acc;
    float _size, rotDia;
    float diamCoe;
		
};
