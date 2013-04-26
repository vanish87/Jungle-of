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

		//player_camera_.setupPerspective(false, 60.0f, 1, 1000);
        player_camera_.enableOrtho();
		player_camera_.setPosition(0,0,500);
		player_camera_.lookAt(ofVec3f(0,0,0));

		butterfly_ = new ButterFly();
        
		wind_.Init();
		wind_.Enable(true,ofVec3f(200,200,0));

		test_.push_back(ofVec3f(400, 100, 0));
		test_.push_back(ofVec3f(300, 200, 0));
		test_.push_back(ofVec3f(300, 300, 0));
		test_.push_back(ofVec3f(200, 300, 0));
        
        if(Jungle::KINECT_ENABLE)
            detected_ = false;
        else
            detected_ = true;
        
        camera_moving_ =false;

    };
    Player::~Player(void)
    {
    }
    
    void Player::Update()
    {
        ofxUser* user = JungleApp::KinectInstance().users;
        ofVec3f l_hand_pos;
        ofVec3f r_hand_pos;
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
                
                
				ofVec3f l_hand_pos = bone.left_hand;
				ofVec3f r_hand_pos = bone.right_hand;
				ofVec3f hand_pos = l_hand_pos - r_hand_pos;
                
				pre_hand_pos_ = hand_pos_;
				ofVec3f p;
				p.x = ofMap(r_hand_pos.x , 0, 640, 0, ofGetWindowWidth(), true);
				p.y = ofMap(r_hand_pos.y , 0, 480, 0, ofGetWindowHeight(), true);
				SetHandPos(p);
			}
		}
        
        if(!detected_)
        {
            butterfly_->Update(ofGetLastFrameTime());
            return;
        }
        if(Jungle::KINECT_ENABLE)
            wind_.Update(hand_radius_, 50, max_hand_radius_, l_hand_pos,r_hand_pos);
        else
            wind_.Update(hand_radius_, 50, max_hand_radius_, hand_pos_, ofVec3f(0,0,0));



		int x_ = ofGetWindowPositionX();
		int y_ = ofGetWindowPositionY();

		int w_ = ofGetWindowWidth();
		int h_ = ofGetWindowHeight();

		ofVec4f vs_d = ofVec4f(0,0,22,0);
		ofVec4f prj_d = vs_d * player_camera_.getProjectionMatrix();
		float ndc_d = prj_d.z/prj_d.w;

		float Zv = 22;
		if(!path_.empty())
		{
			ofVec3f path_pos;// = path_.front().first;

			inter_time_ += 0.1;
			float t = inter_time_ / 1.0f;
			if(path_.size() > 3)
			{

				ofVec3f inter_pos = crspline_.GetPos(path_[0].first, path_[1].first, path_[2].first, path_[3].first, t);
				path_pos = inter_pos;

			}
			else
			{
				if(path_.size() == 3)
				{
					ofVec3f inter_pos = crspline_.GetPos(path_[0].first, path_[1].first, path_[2].first, path_[2].first, t);
					path_pos = inter_pos;
				}
				else
				{
					if(path_.size() == 2)
					{
						//path_pos.x = ofLerp(path_[0].first .x, path_[1].first.x, inter_time_);
						//path_pos.y = ofLerp(path_[0].first .y, path_[1].first.y, inter_time_);
						ofVec3f inter_pos = crspline_.GetPos(path_[0].first, path_[1].first, path_[1].first, path_[1].first, t);
						path_pos = inter_pos;//path_.back().first;
					}
					else
					{
						path_pos.x = ofLerp(butterfly_pos_ss_.x, path_[0].first.x, inter_time_);
						path_pos.y = ofLerp(butterfly_pos_ss_.y, path_[0].first.y, inter_time_);
					}
				}
			}
			if (inter_time_ > 1.0f) 
			{

				inter_time_ = 0;
				//if(path_.size() == 2) inter_time_ = 1.0f;
				if(path_.size() > 2)
					path_.erase(path_.begin());
			}

			butterfly_pos_ss_ = path_pos;
			ofVec4f ndc = ofVec4f((path_pos.x - (x_/2 + w_/2)) * 2.0f/w_, (h_- path_pos.y - (y_/2 + h_/2)) * 2.0f/h_, 1,1);
			ofVec4f pproj = ndc * Zv;
			ofMatrix4x4 mat;
			mat.makeInvertOf(player_camera_.getProjectionMatrix());
			ofVec4f vs_pos = pproj * mat;
			//vs_pos = vs_pos/vs_pos.w;
			vs_pos.w= 1;
			//vs_pos.z = 22;
			mat.makeInvertOf(player_camera_.getModelViewMatrix());
			ofVec3f ws_pos = vs_pos * mat;

			butterfly_->butterfly_pos_ = ws_pos;
		}
       // if(!camera_moving_)
            camera_pos_ = ofVec3f(butterfly_->getPosition().x, butterfly_->getPosition().y, 0);
		ofVec3f old_pos = player_camera_.getPosition();
		old_pos.z = 0;
		ofVec3f delta = camera_pos_ - old_pos;
		if(delta.length() > 7 )
		{
           // camera_moving_ = true;
			old_pos += delta / 30;
			//player_camera_.setPosition(old_pos.x, old_pos.y,player_camera_.getPosition().z);
		}
        if(delta.length() < 0.1)
        {
            ;//camera_moving_ = false;
        }

        
        //cout<<delta.length()<<endl;

		butterfly_->Update(ofGetLastFrameTime());
		//cout<<camera_pos_.x<< " "<<camera_pos_.y<<"\r";
		pre_hand_pos_ = hand_pos_;
		
    }

	ofCamera& Player::GetCamera()
	{
		return player_camera_;
	}

	void Player::SetHandPos( ofVec3f pos )
	{
		hand_pos_ = pos;
        //pos.x = ofClamp(pos.x, 300, 1280-300);
        //pos.y = ofClamp(pos.y, 200, 720-200);
        
		if(!path_.empty())
		{
			ofVec3f back_pos = path_.back().first;
			if ((hand_pos_-back_pos).length() < 50) return;
		}

		if(path_.size() > MAX_PATH_LENGTH )
        {
            if((path_[0].first - path_.back().first).length() > 50)
            {
                for(int i=0;i < 10 ;++i)                    
                    ;//      path_.erase(path_.begin());
            }
                path_.erase(path_.begin());
        }
		path_.push_back(make_pair(pos, ofGetElapsedTimef()));
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