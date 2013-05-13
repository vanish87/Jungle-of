//
//  Animal.cpp
//  openNiSample007
//
//  Created by Yuan Li on 2/25/13.
//  Copyright 2013 nyu. All rights reserved.
//

#include "Cloud.h"
#include "JungleApp.h"

namespace Jungle {
    Cloud::Cloud(void)
	{
		for (size_t i = 0; i < 5; ++i)
		{
			SceneModel droplet;
			droplet.loadModel("Environment/Droplet.obj");
			droplet_.push_back(droplet);
		}
		max_time_ = 0;
		rain_ = false;
    };
    Cloud::~Cloud(void)
    {
    }   


    
    void Cloud::Update(float frame_time)
    {
        if(enable_ && flower_state_ != WAITING)
        {            
            time_ +=frame_time;
        }
		ofVec3f scale = getScale();
		switch (flower_state_)
		{
		case GROWING:
			if(scale.x < max_scale_)
			{
				scale += scale_speed_;
			}
			if(time_ > staying_time_)
			{
                if(falling_)
                {
                    flower_state_ = FALLING;
                    org_pos_ = pos;
                    time_ = 0;
                }
                else
                {
                    flower_state_ = DISAPPEARING;
                    org_pos_ = pos;
                    time_=0;
                }
			}
			if(max_time_ > 1)
				rain_ = true;

			if(rain_)
			{
				UpdateRain();
			}
			break;
		case DISAPPEARING:
			if(scale.x > max_scale_ * 0.3)
				scale -= scale_speed_;
			else
			{
				scale = ofVec3f(0, 0, 0);
				pos = org_pos_;
				flower_state_ = WAITING;
				time_ = 0;
			}
			break;
		case HOLDING:		
			if (time_ > holding_time_)
            {
				flower_state_ = GROWING;
				
                
                //playing fruit sound
                if(falling_)
                {
                    
                }
                //playing leaf sound
                else
                {                    
                    int index = ofRandom(0,4);
                    if (!sounds_[index].getIsPlaying())
                    {
                        sounds_[index].play();
                        sounds_[index].setSpeed(pitch_);
                    }
                }
				time_ = 0;
			}			
			break;
		case WAITING:
                if(rain_)
                {
                  rain_=!rain_;
                  droplet_pos_.clear();
                }
			break;
		default:
			break;
		}            
		setScale(scale.x, scale.y, scale.z);      
	}

	void Cloud::Draw()
	{
		ofSetColor(color_.r, color_.g, color_.b,color_.a);
		if(enable_)
		{
			switch (flower_state_)
			{
			case GROWING:
			case DISAPPEARING:
			case FALLING:
			case WAITING:
				drawFaces();
				break;
			case HOLDING:
				{
					ofSetColor(circle_color_);
					float scale = (holding_time_ - time_)/holding_time_;
					if(time_ <= 0.1)
						scale = 1;
					ofPushMatrix();
					ofTranslate(pos.x, pos.y);
					triggering_circle_.setScale(circle_size_.x * scale, circle_size_.x* scale, circle_size_.x* scale);
					//triggering_circle_.drawFaces();
					// 					triggering_circle_.draw(-circle_size_.x * scale, -circle_size_.y * scale,
					// 						circle_size_.z * scale, circle_size_.w * scale);
					ofPopMatrix();
				}
				break;
			}

			if(rain_)
				for(vector<ofVec3f>::iterator it = droplet_pos_.begin(); it != droplet_pos_.end(); ++it)
				{
                    SceneModel dmodel = droplet_[ofRandom(0, droplet_.size())];
                    dmodel.setPosition(it->x, it->y, it->z);
					dmodel.drawFaces();
				}
		}
	}

	void Cloud::InitDroplet()
	{
		for(vector<SceneModel>::iterator it = droplet_.begin(); it != droplet_.end(); ++it)
		{
			ofVec3f dpos = pos;
			dpos.x += 50 * ofRandom(-1,1);
			dpos.y += 20 * ofRandom(-1,1);
			it->setPosition(dpos.x, dpos.y,dpos.z);
			it->setRotation(0,180,1,0,0);
            it->setRotation(1, 45, 0, 0, 1);            
			it->setScale(0.1, 0.1/1.414,0.1);
		}
	}
    
    void Cloud::UpdateRain()
    {
        if(droplet_pos_.size() < 70 && ofRandom(0,1)< 0.3)
        {
            ofVec3f dpos = pos;
			dpos.x += 50 * ofRandom(-1,1);
			dpos.y += 20 * ofRandom(-1,1);
            droplet_pos_.push_back(dpos);
            speed_.push_back(ofRandom(3,10));
        }
        vector<float>::iterator sit = speed_.begin();
        for(vector<ofVec3f>::iterator it = droplet_pos_.begin(); it!= droplet_pos_.end(); ++it,++sit)
        {
            ofVec3f dpos = *it;
            if(dpos.y < 0)
            {
                dpos = pos;
                dpos.x += 50 * ofRandom(-1,1);
                dpos.y += 20 * ofRandom(-1,1);
                //rain_ = false;
            }
            it->set(dpos.x, dpos.y - *sit,dpos.z);
        }
    }

	void Cloud::Triggering( bool trigger )
	{
		Flower::Triggering(trigger);
		if(trigger)
		{
			max_time_ += ofGetLastFrameTime();
		}
		else
        {
            rain_ = false;
        }
	}

    
}