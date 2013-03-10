#ifndef JUNGLE_APP_
#define JUNGLE_APP_

#pragma once
#include "ofMain.h"
#include "StateManager.h"
#include "GamingScene_1.h"
#include "GamingScene2.h"
#include "GamingScene3.h"
#include "GamingScene4.h"

namespace Jungle
{

	static const bool KINECT_ENABLE = false;
	class JungleApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
 		void windowResized(int w, int h);

		static StateManager& StateManagerInstance();
		static ofxKinectUsers& KinectInstance();

	private:
		GamingScene_1* game_1_;
		GamingScene2* game_2_;
		GamingScene3* game_3_;
		GamingScene4* game_4_;


		void	inPose(ofxUser & user);
		void	inGesture(ofxUser & user);
		void	userIn(ofxUser & user);
		void	userMove(ofxUser & user);
		void	userOut(ofxUser & user);
        
	};

}
#endif
