#ifndef GAMESCENE1_
#define GAMESCENE1_

#pragma once
#include "State.h"
#include "ofxAssimpModelLoader.h"
#include "ofImage.h"

//#include "ofxGifDecoder.h"
//#include "ofxGifFile.h"

namespace Jungle
{
	class GamingScene_1 :
		public State
	{
	public:
		GamingScene_1(void);
		~GamingScene_1(void);

		virtual void Steup();

		virtual void Update();

		virtual void Draw();

		virtual void inPose( ofxUser & user );

		virtual void inGesture( ofxUser & user );

		virtual void userIn( ofxUser & user );

		virtual void userMove( ofxUser & user );

		virtual void userOut( ofxUser & user );

		virtual void keyPressed( int key );

		virtual void mouseDragged( int x, int y, int button );
        
        virtual void windowResized(int w, int h);

	private:
		//ofxGifDecoder giraffe_decoder_;
		//ofxGifFile giraffe_;
        ofImage background_;
		bool giraffe_enabled_;
		ofxAssimpModelLoader bird_;
		bool bird_enabled_;
		ofxAssimpModelLoader elephant_;
		bool elephant_enabled_;
		ofxAssimpModelLoader scene_background_;


		float animation_time_;
		int frame_index_;
        
        int w_;
        int h_;

		ofLight light_;

	};

}

#endif // !GAMESCENE1_


