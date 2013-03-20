#ifndef GAMESCENE4_H_
#define GAMESCENE4_H_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"
#include "ofx3DParticleEmitter.h"
#include "ButterFly.h"

namespace Jungle
{
	class GamingScene4 :public State
	{
	public:
		GamingScene4(void);
		~GamingScene4(void);

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
		ofxAssimpModelLoader sphere_;
		ofVec3f sphere_pos_;
		float sphere_radius_;
		bool sphere_collided_;
		int tree_rotation_;
        
        float bird_rotation_;

		ofImage right_wind_;
		ofVec3f rw_pos_;
		bool rw_enabled_;

		ButterFly bird_;
		float animation_time_;
		ofVec3f bird_pos_;
        ofVec3f bird_pos_ss_;
		ofVec3f bird_rot_;
        
        ofVec3f bird_acc_;
        ofVec3f bird_vol_;
        
        float angle_;
        
		ofxAssimpModelLoader shadow_;
		ofVec3f shadow_pos_;

		ofCamera main_camera_;
		//the imaginary obj that camera look at
		ofNode virtual_looking_obj_;
		//longitude(x), latitude(y) of orbit camera radius(z)
		ofVec3f camera_orbit_para_;
        ofMatrix4x4 mvp_mat_;
        
        ofxParticleEmitter		emitter_;
		float particle_scale_;
		ofPoint hand_pos_;
		ofPoint pre_hand_pos_;

		float gesture_timer_;
		bool left_wind_start_;
		bool right_wind_start_;

		int w_;
		int h_;
		int x_;
		int y_;
	};

}

#endif

