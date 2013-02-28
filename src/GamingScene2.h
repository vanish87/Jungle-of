#ifndef GAMESCENE2_
#define GAMESCENE2_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"

namespace Jungle
{
	class GamingScene2
		:public State
	{
	public:
		GamingScene2(void);
		~GamingScene2(void);

		virtual void Steup();

		virtual void Update();

		virtual void Draw();

		virtual void keyPressed( int key );

		virtual void keyReleased( int key );

		virtual void inPose( ofxUser & user );

		virtual void inGesture( ofxUser & user );

		virtual void userIn( ofxUser & user );

		virtual void userMove( ofxUser & user );

		virtual void userOut( ofxUser & user );

	private:
		ofxAssimpModelLoader stage_;
		ofxAssimpModelLoader shadow_;
		ofxAssimpModelLoader bird_;
		bool bird_enable_;
		vector<ofxAssimpModelLoader> trees_;
		ofVec3f shadow_pos_;
		ofCamera main_camera_;
		ofLight light_;

		int w_;
		int h_;
		int x_;
		int y_;

	};
}

#endif

