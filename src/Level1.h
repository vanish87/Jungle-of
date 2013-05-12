#ifndef LEVEL1_H_
#define LEVEL1_H_

#pragma once
#include "State.h"
#include "ofVec3f.h"
#include "ofLight.h"
#include "Flower.h"
#include "ofSoundPlayer.h"

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
		ofVec3f start_pos_;
        
        ofLight light_;
        float angle_;
        
        unsigned int max_leaf_;
        
        vector<Flower> mushrooms_;
        int index_;
        
		vector<vector<ofColor> > stage_color_;
        ofImage title_;
		bool show_title;

		//ofImage circle_;

		int w_;
		int h_;
		int x_;
		int y_;
       
        
//        ofSoundPlayer trigger1;
//        ofSoundPlayer trigger2;
	};
}

#endif

