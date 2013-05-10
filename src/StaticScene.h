#ifndef STATIC_SCENE_H_
#define STATIC_SCENE_H_

#pragma once
#include "State.h"
#include "SceneModel.h"

namespace Jungle
{
	class StaticScene :public State
	{
	public:
		StaticScene(void);
		~StaticScene(void);

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
		SceneModel tree_;
        SceneModel tree1_;
        SceneModel tree2_;
        SceneModel tree3_;
        SceneModel tree4_;
        SceneModel tree5_;
        SceneModel bg_1_;
        SceneModel bg_2_;
        SceneModel bg_3_;        
        SceneModel bg_4_;
        SceneModel ground_1_;
        SceneModel ground_2_;
        SceneModel ground_3_;
        SceneModel ground_4_;
        SceneModel ground_5_;

        SceneModel ground_;
        SceneModel rocks_;
        SceneModel bush_;
        
		SceneModel* model_ ;
        
        ofColor back_color_start_;
        ofColor back_color_end_;

		int w_;
		int h_;
		int x_;
		int y_;
		
		ofSoundPlayer atmo;
	};

}

#endif

