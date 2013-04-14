#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "ofNode.h"
#include "ofCamera.h"
#include "ofx3DParticleEmitter.h"
#include "ButterFly.h"

namespace Jungle {
    class Player : public ofNode
    {
    public:
        Player(void);
        ~Player(void);
        
        void Update();

		ofCamera& GetCamera();
		void SetHandPos( ofVec3f pos );
		ButterFly& GetButterfly();
		ofVec3f GetHandPos();
	public:
		ofCamera player_camera_;
		ButterFly* butterfly_;

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
		bool start_timing_;
		bool track_moving_;
		bool interval_;
		float interval_time_;
        
        ofxParticleEmitter emitter_;
        ofxParticleEmitter max_emitter_;

	//private copy constructor to avoid inconsistent of Singleton Pattern
	private:
		Player(const Player& rhs);
    };
}


#endif
