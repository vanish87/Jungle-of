#ifndef GAMESCENE6_H_
#define GAMESCENE6_H_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"
#include "ofx3DParticleEmitter.h"
#include "ButterFly.h"
#include "WindParticle.h"
#include "Flower.h"

namespace Jungle
{
	class GamingScene6 :public State
	{
	public:
		GamingScene6(void);
		~GamingScene6(void);

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
		ofCamera main_camera_;
		ofVec3f camera_pos_;

		ofVec3f hand_pos_;
		ofVec3f pre_hand_pos_;
		ofVec3f start_pos_;
		ofVec3f hand_vel_;
		float vlength;
		float hand_radius_;
		float max_hand_radius_;
		float hand_mass_;

		float moving_time_;
		bool moving_;
		bool track_moving_;
		bool interval_;
		float interval_time_;

		ofVec3f butterfly_pos_;
		ofVec3f butterfly_vel_;
		ofVec3f butterfly_force_;
		float butterfly_radius_;
		float butterfly_mass_;

		int w_;
		int h_;
		int x_;
		int y_;
	};

}

#endif

