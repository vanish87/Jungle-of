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
        SceneModel bg_1_;
        SceneModel bg_2_;
        SceneModel bg_3_;
        SceneModel ground_;


		SceneModel* model_ ;

		int w_;
		int h_;
		int x_;
		int y_;
		
		ofSoundPlayer atmo;
	};

}

#endif

