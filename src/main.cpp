#include "ofMain.h"
#include "JungleApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
    //window.setGlutDisplayString("rgba double samples>=4");
	//ofSetupOpenGL(&window, 1024,768, OF_WINDOW);			// <-------- setup the GL context
	ofSetupOpenGL(&window, 1280,720, OF_WINDOW);
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new Jungle::JungleApp());

}
