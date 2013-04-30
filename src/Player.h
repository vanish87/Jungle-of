#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once

#include "ofNode.h"
#include "ofCamera.h"
#include "WindGenerator.h"


namespace Jungle {
	
    class Player : public ofNode
    {
    public:
        Player(void);
        ~Player(void);
        
        void Update();

		ofCamera& GetCamera();
		void SetHandPos( ofVec3f pos );
		ofVec3f GetHandPos();

	public:
		ofCamera player_camera_;
		ofVec3f camera_pos_;        
        
        ofVec3f l_hand_pos_;
        ofVec3f r_hand_pos_;
		        
        bool detected_;
        
		WindGenerator wind_;
		
	//private copy constructor to avoid inconsistent of Singleton Pattern
	private:
		Player(const Player& rhs);

    };
}


#endif
