#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    ofAppGlutWindow window;
<<<<<<< HEAD
	ofSetupOpenGL(&window,1920, 1080,OF_WINDOW);			// <-------- setup the GL context
=======
	ofSetupOpenGL(&window, 1920,1080,OF_WINDOW);			// <-------- setup the GL context
>>>>>>> 141cf61acd2246c8c47145334110642a567d13e7

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new testApp());
}
