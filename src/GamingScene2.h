#ifndef GAMESCENE2_
#define GAMESCENE2_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"

namespace Jungle
{
    static const int MAX_SPEED = 1;
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
		ofxAssimpModelLoader background_;
		ofxAssimpModelLoader shadow_;
		ofxAssimpModelLoader bird_;
        ofVec3f bird_pos_;
        float bird_speed_;
        bool flying_;
        
		bool bird_enable_;
		vector<ofxAssimpModelLoader> trees_;
		ofVec3f shadow_pos_;
		ofCamera main_camera_;
        
        ofVec3f look_at_;
		ofLight light_;

		ofImage hand_;
		ofPoint hand_pos_;

		ofImage tree_button_1_;
		ofPoint tree_button_pos_1_;
		float button_1_time_;
        bool button_1_pressed_;
        
		ofImage tree_button_2_;
		ofPoint tree_button_pos_2_;
		float button_2_time_;        
        bool button_2_pressed_;

		ofVec3f sphere_pos_;
		float sphere_radius_;
		float stayed_time_;
		bool sphere_collided_;

		ofImage loading_;
		ofPoint loading_pos_;

		int w_;
		int h_;
		int x_;
		int y_;

	};
}

#endif

