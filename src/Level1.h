#ifndef LEVEL1_H_
#define LEVEL1_H_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"
#include "ButterFly.h"
#include "WindGenerator.h"
#include "Flower.h"

namespace Jungle
{
	class Level1 :public State
	{
	public:
		Level1(void);
		~Level1(void);

		virtual void Steup();

		virtual void Update();

		virtual void Draw();

		virtual void keyPressed( int key );

		virtual void mouseMoved( int x, int y );

		virtual void windowResized( int w, int h );

		virtual void inPose( ofxUser & user );

		virtual void inGesture( ofxUser & user );

		virtual void userIn( ofxUser & user );

		virtual void userMove( ofxUser & user );

		virtual void userOut( ofxUser & user );

	private:
		ofLight light_;
		ofxAssimpModelLoader stage_;
		ofVec3f stage_pos_;

		vector<Flower> mushrooms_;

		ButterFly butterfly_;		
		ofVec3f butterfly_pos_;
		ofVec3f butterfly_acc_;
		ofVec3f butterfly_vol_;
		float butterfly_mass_;

		float animation_time_;

		ofCamera main_camera_;
		ofVec3f camera_pos_;

		WindGenerator wind_;
		ofVec3f hand_pos_;
		ofPoint pre_hand_pos_;

		bool two_hands_;


		int w_;
		int h_;
		int x_;
		int y_;
	};
}

#endif

