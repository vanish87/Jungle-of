#ifndef GAMESCENE5_H_
#define GAMESCENE5_H_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"
#include "ofx3DParticleEmitter.h"
#include "ButterFly.h"

namespace Jungle
{
	class GamingScene5 :public State
	{
	public:
		GamingScene5(void);
		~GamingScene5(void);

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
		ofxAssimpModelLoader background_;
		ofVec3f sphere_pos_;
		bool in_sphere_;
		bool need_move_;
		float sphere_radius_;

		ButterFly bird_;
		float animation_time_;
		ofVec3f bird_pos_;
        ofVec3f bird_pos_ss_;
		ofVec3f bird_rot_;
        
        ofVec3f bird_acc_;
        ofVec3f bird_vol_;
        
        

		ofCamera main_camera_;
		ofVec3f camera_pos_;

		ofPoint hand_pos_;
		ofPoint pre_hand_pos_;


		int w_;
		int h_;
		int x_;
		int y_;
	};

}

#endif

