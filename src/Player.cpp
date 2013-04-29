#include "Player.h"
#include "JungleApp.h"

namespace Jungle 
{

	const unsigned int MAX_PATH_LENGTH = 50;
    Player::Player(void)
		:wind_("")
	{
		hand_pos_.set(200,200,0);
		pre_hand_pos_ = hand_pos_;

        player_camera_.enableOrtho();
		player_camera_.setPosition(0,0,500);
		player_camera_.lookAt(ofVec3f(0,0,0));
        
		wind_.Init();
		wind_.Enable(true,ofVec3f(200,200,0));
        
        if(Jungle::KINECT_ENABLE)
            detected_ = false;
        else
            detected_ = true;

    };
    Player::~Player(void)
    {
    }
    
    void Player::Update()
    {
        ofxUser* user = JungleApp::KinectInstance().users;
		for(int i =0; i< MAX_USERS; ++i)
		{
			if(user[i].isActive&& user[i].bones)
			{
                detected_ = true;
				Bones bone = user[i].bonesPoints;
				ofVec3f torsor_pos = bone.torso;
				torsor_pos.x = ofMap(torsor_pos.x ,
                                     MIN_KINECT_AREA.x, MAX_KINECT_AREA.x, MIN_PLAY_AREA.x, MAX_PLAY_AREA.x, true);
				torsor_pos.z = ofMap(torsor_pos.z ,
                                     MIN_KINECT_AREA.z, MAX_KINECT_AREA.z, MIN_PLAY_AREA.z, MAX_PLAY_AREA.z, true);
                
                
				//ofVec3f l_hand_pos;
                l_hand_pos_.set(bone.left_hand.x, bone.left_hand.y, 0);
                r_hand_pos_.set(bone.right_hand.x,bone.right_hand.y,0);
				//ofVec3f hand_pos = l_hand_pos - r_hand_pos;
                
				pre_hand_pos_ = hand_pos_;
				ofVec3f p;
				p.x = ofMap(l_hand_pos_.x , 0, 640, 0, ofGetWindowWidth(), true);
				p.y = ofMap(l_hand_pos_.y , 0, 480, 0, ofGetWindowHeight(), true);
                l_hand_pos_.x = p.x;
                l_hand_pos_.y = p.y;
                
				p.x = ofMap(r_hand_pos_.x , 0, 640, 0, ofGetWindowWidth(), true);
				p.y = ofMap(r_hand_pos_.y , 0, 480, 0, ofGetWindowHeight(), true);
                r_hand_pos_.x = p.x;
                r_hand_pos_.y = p.y;
                
				SetHandPos(p);
			}
		}
        
        if(!detected_)
        {
            return;
        }
        if(Jungle::KINECT_ENABLE)
            wind_.Update(l_hand_pos_,r_hand_pos_);
        else
            wind_.Update(hand_pos_, ofVec3f(0,0,0));
		
		pre_hand_pos_ = hand_pos_;
		
    }

	ofCamera& Player::GetCamera()
	{
		return player_camera_;
	}

	void Player::SetHandPos( ofVec3f pos )
	{
		hand_pos_ = pos;		
	}
	ofVec3f Player::GetHandPos()
	{
		return hand_pos_;
	}





    
}