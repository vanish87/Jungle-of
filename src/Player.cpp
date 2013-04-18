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
		hand_vel_.set(0,0,0);
		hand_radius_ = 50;
		max_hand_radius_ = 70;
		hand_mass_ = 1;

		moving_time_ = 0;
		moving_ = false;
		start_timing_ = false;
		track_moving_ = false;
		interval_ = false;
		interval_time_ = 0;

		player_camera_.setupPerspective(false, 60.0f, 1, 1000);
		player_camera_.setPosition(0,20,50);
		player_camera_.lookAt(ofVec3f(0,20,0));

		butterfly_ = new ButterFly();
        
		wind_.Init();
		wind_.Enable(true,ofVec3f(200,200,0));


    };
    Player::~Player(void)
    {
    }
    
    void Player::Update()
    {

		wind_.Update(hand_radius_, 50, max_hand_radius_, hand_pos_);

		if((hand_pos_-pre_hand_pos_).length() < 5)
		{
			if(!path_.empty())
				path_.erase(path_.begin());
		}
		ofxUser* user = JungleApp::KinectInstance().users;
		for(int i =0; i< MAX_USERS; ++i)
		{
			if(user[i].isActive&& user[i].bones)
			{
				Bones bone = user[i].bonesPoints;
				ofVec3f torsor_pos = bone.torso;
				torsor_pos.x = ofMap(torsor_pos.x , 
					MIN_KINECT_AREA.x, MAX_KINECT_AREA.x, MIN_PLAY_AREA.x, MAX_PLAY_AREA.x, true);
				torsor_pos.z = ofMap(torsor_pos.z ,
					MIN_KINECT_AREA.z, MAX_KINECT_AREA.z, MIN_PLAY_AREA.z, MAX_PLAY_AREA.z, true);


				ofVec3f l_hand_pos = bone.left_hand;
				ofVec3f r_hand_pos = bone.right_hand;
				ofVec3f hand_pos = l_hand_pos - r_hand_pos;

				pre_hand_pos_ = hand_pos_;
				hand_pos_.x = ofMap(r_hand_pos.x , 0, 640, 0, ofGetWindowWidth(), true);
				hand_pos_.y = ofMap(r_hand_pos.y , 0, 480, 0, ofGetWindowHeight(), true);
			}
		}

		if((pre_hand_pos_ - hand_pos_).length() < 3 && !interval_)
		{
			hand_radius_ +=0.3;
		}
		else
		{
			hand_radius_ -= 1;
		}

		hand_radius_ = ofClamp(hand_radius_, 50, max_hand_radius_);
		if (hand_radius_ == max_hand_radius_ && !interval_)
		{
			track_moving_ = true;
			start_pos_ = hand_pos_;
		}

		butterfly_->butterfly_force_ = ofVec3f(0,0,0);
		if (track_moving_)
		{
			if((pre_hand_pos_ - hand_pos_).length() > 20)
				start_timing_ = true;
			if(start_timing_)
				moving_time_ +=ofGetLastFrameTime();

			if(moving_time_ > 0.5)
			{
				hand_vel_ = hand_pos_ - start_pos_;
				vlength =hand_vel_.length();
				if( vlength > 40) //minimum required distance moved for the particles to have an impact on butterfly, measured in pixels
				{
					butterfly_->butterfly_force_ += hand_vel_.getNormalized() * 10;
					cout<<"apply force"<<butterfly_->butterfly_force_.x<<" "<<butterfly_->butterfly_force_.y<<endl;
					interval_ = true;
				}
				moving_time_ = 0;
				track_moving_ = false;
				start_timing_= false;
                hand_radius_ = 50;
			}
		}

		if(interval_)
		{
			interval_time_+=ofGetLastFrameTime();
			if(interval_time_ > 1.5)
            {
                interval_time_ = 0;                
				interval_ = false;
            }
		}

		butterfly_->Update(ofGetLastFrameTime());

		int x_ = ofGetWindowPositionX();
		int y_ = ofGetWindowPositionY();

		int w_ = ofGetWindowWidth();
		int h_ = ofGetWindowHeight();

		ofVec4f bird_pos_(0,20,28,1);
		ofMatrix4x4 mat_ = player_camera_.getModelViewMatrix();

		ofVec4f bird_pos_ss_= bird_pos_ * mat_ ;
		mat_ = player_camera_.getProjectionMatrix();
		ofVec4f ss = bird_pos_ss_ * mat_;
		ofPoint screen_pos;
		screen_pos.set(ss.x * w_/2 + (x_/2 + w_/2), h_ - (ss.y * h_/2 + (y_/2 + h_/2)));

		//bird_pos_ss_.set(screen_pos.x, screen_pos.y);

		ofVec4f vs_d = ofVec4f(0,0,22,0);
		ofVec4f prj_d = vs_d * player_camera_.getProjectionMatrix();
		float ndc_d = prj_d.z/prj_d.w;

		float Zv = 22;
		if(!path_.empty())
		{
			ofVec4f ndc = ofVec4f((path_.front().x - (x_/2 + w_/2)) * 2.0f/w_, (h_- path_.front().y - (y_/2 + h_/2)) * 2.0f/h_, 1,1);
			ofVec4f pproj = ndc * Zv;
			ofMatrix4x4 mat;
			mat.makeInvertOf(player_camera_.getProjectionMatrix());
			ofVec4f vs_pos = pproj * mat;
			//vs_pos = vs_pos/vs_pos.w;
			vs_pos.w= 1;
			//vs_pos.z = 22;
			mat.makeInvertOf(player_camera_.getModelViewMatrix());
			ofVec3f ws_pos = vs_pos * mat;
			butterfly_->setPosition(ws_pos.x, ws_pos.y, ws_pos.z);
		}
        
        //player_camera_.setPosition(butterfly_->butterfly_pos_.x, butterfly_->butterfly_pos_.y, player_camera_.getPosition().z);

		//cout<<(pre_hand_pos_ - hand_pos_).x<< " "<<(pre_hand_pos_ - hand_pos_).y<<"\r";
		pre_hand_pos_ = hand_pos_;
		
    }

	ofCamera& Player::GetCamera()
	{
		return player_camera_;
	}

	void Player::SetHandPos( ofVec3f pos )
	{
		hand_pos_ = pos;		
		if(!path_.empty() && (hand_pos_-path_.back()).length() < 5) return;

		if(path_.size() > MAX_PATH_LENGTH )
			path_.erase(path_.begin());
		path_.push_back(pos);
	}

	ButterFly& Player::GetButterfly()
	{
		return *butterfly_;
	}

	ofVec3f Player::GetHandPos()
	{
		return hand_pos_;
	}
	


    
}