#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once

#include "ofNode.h"
#include "ofCamera.h"
#include "ButterFly.h"
#include "WindGenerator.h"

#include "CRSpline.h"

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
		ofVec3f camera_pos_;
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
        
		WindGenerator wind_;
		float inter_time_;

		ofVec3f butterfly_pos_ss_;

	//private copy constructor to avoid inconsistent of Singleton Pattern
	private:
		Player(const Player& rhs);

	public:
		vector<pair<ofVec3f, float>> path_;
		vector<ofVec3f> test_;
		CRSpline crspline_;
    };
}


#endif
