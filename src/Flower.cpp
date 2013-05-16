//
//  Animal.cpp
//  openNiSample007
//
//  Created by Yuan Li on 2/25/13.
//  Copyright 2013 nyu. All rights reserved.
//

#include "Flower.h"
#include "JungleApp.h"

namespace Jungle {
    Flower::Flower(void)
    : color_(255,255,255,100), max_scale_(0.008), scale_speed_(0.001), collide_size_(70)
    {
        setScale(0, 0, 0);
		//triggering_circle_.loadModel("UI/Trigger.obj");
		//triggering_circle_.setRotation(0, 90, 0, 1, 0);
		SetCircleSize(200);
        flower_state_ = WAITING;
        
        circle_color_ = ofColor(255,255,255,255);
        
        //in seconds
        holding_time_ = 3;
        staying_time_ = 5;
        
        pitch_ = 1.0f;
        triggering_time_ = 0;
        
		sounds_[0].loadSound("audio/leaves-1.mp3");
		sounds_[1].loadSound("audio/leaves-2.mp3");
		sounds_[2].loadSound("audio/leaves-3.mp3");
		sounds_[3].loadSound("audio/leaves-4.mp3");
		sounds_[4].loadSound("audio/fall-1.mp3");
		sounds_[5].loadSound("audio/fall-2.mp3");
    };
    Flower::~Flower(void)
    {
    }
    
    void Flower::SetColor(ofColor color)
    {
        color_ = color;
    }
    
    void Flower::SetCircleColor(ofColor color)
    {
        circle_color_ = color;
    }
    void Flower::SetFalling(bool falling)
    {
        falling_ = falling;
    }
    void Flower::SetPitch(float pitch)
    {
        pitch_ = pitch;
        org_pos_ = pos;
    }
    
    void Flower::Update(float frame_time)
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
//                if(falling_)
//                {
//                        flower_state_ = FALLING;
//                        org_pos_ = pos;
//                        time_ = 0;
//                        triggering_time_ = 0;
//                    
//                }
//                else
                //if(!falling_)
                {
                    flower_state_ = DISAPPEARING;
                    org_pos_ = pos;
                    time_=0;
                }
			}
			break;
		case DISAPPEARING:
			if(scale.x > max_scale_ * 0.3)
				scale -= scale_speed_;
			else
			{
				scale = ofVec3f(0, 0, 0);
                if(falling_)
                    pos = org_pos_;
				flower_state_ = WAITING;
				time_ = 0;
                triggering_time_ = 0;
			}
			break;
		case HOLDING:		
			if (time_ > holding_time_)
            {
				flower_state_ = GROWING;
				
                

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
		case FALLING:
			if(pos.y > 10)
            {
                //pos.x += sin(ofGetElapsedTimef())* ofRandom(-10,10);
				pos.y-=3;
            }
			else
			{
                //play one of two droping sounds
                int index = ofRandom(4,6);
                if (!sounds_[index].getIsPlaying() && time_ < 0.5)
                {
                    sounds_[index].setVolume(0.7);
                    sounds_[index].play();
                }
                if(time_ > 4)
                {
                    flower_state_ = DISAPPEARING;
                    time_ = 0;
                }
			}
			break;
		default:
			break;
		}            
		setScale(scale.x, scale.y, scale.z);       
        

    }
    
    void Flower::Draw()
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
		}

		
    }
    
    
    void Flower::SetMaxScale(float scale)
    {
        max_scale_ = scale;
    }

	ofVec3f Flower::GetScreenPos( ofVec3f world_pos, ofCamera& camera )
	{
		int w = ofGetWindowWidth();
		int h = ofGetWindowHeight();
		int x = ofGetWindowPositionX();
		int y = ofGetWindowPositionY();
		ofMatrix4x4 mvp_mat_ = camera.getModelViewProjectionMatrix();
		ofVec3f pos_ss;
		pos_ss= world_pos * mvp_mat_ ;
		ofPoint screen_pos;
		screen_pos.set(pos_ss.x * w/2 + (x/2 + w/2), h - (pos_ss.y * h/2 + (y/2 + h/2)));
		return screen_pos;
	}

	void Flower::SetCircleSize( float size )
	{
		circle_size_.z= circle_size_.w = size;
		circle_size_.x = size/320;
		circle_size_.y = 3*circle_size_.x/4;

	}

	void Flower::SetScaleSpeed( float speed )
	{
		scale_speed_ = speed;
	}

	bool Flower::Collided( ofVec3f pos )
	{
		int h_ = ofGetWindowHeight();
		ofVec3f bt_pos = pos;
		bt_pos.z = 0;
		bt_pos.y = h_-bt_pos.y;
		ofVec3f mh_pos = ofVec3f(getPosition().x, getPosition().y, 0);
		if( (bt_pos - mh_pos).length() < collide_size_)
			return true;
		else
		{
			return false;
		}
	}

	void Flower::SetCollideSize( float size )
	{
		collide_size_ = size;
	}


	bool Flower::IsGrowing()
	{
		return (flower_state_ == GROWING && !(scale.x < max_scale_));
	}

	void Flower::SetGrowing()
	{
		if(flower_state_ == WAITING )
		{
			flower_state_ = GROWING;
		}
	}

	void Flower::Triggering( bool trigger )
	{
		if(!enable_) enable_ = true;
		if(trigger)
		{
			if(flower_state_ == WAITING)
			{
				flower_state_ = HOLDING;
				time_ = 0;
			}
			else
			if (flower_state_ == DISAPPEARING)
			{
				//flower_state_ = GROWING;
				//time_ = 0;
			}
			else
			if(flower_state_ == GROWING)
				time_ = 0;
            
            if(falling_)
            {
                triggering_time_+=ofGetLastFrameTime();
                if(triggering_time_ > 0.5 && flower_state_ == GROWING)
                {
					
                    org_pos_ = pos;
                    flower_state_ = FALLING;
                }
            }
          
		}
		else
		{
			if(flower_state_ == HOLDING)
			{
				flower_state_ = WAITING;
				time_ = 0;
			}
		}
	}

	void Flower::SetDisapp()
	{
		if(flower_state_ == GROWING)
		{
			flower_state_ = FALLING;
			org_pos_ = pos;
			time_ = 0;
		}
	}

	void Flower::Reset()
	{
		time_ = 0;
		pos = org_pos_;
		flower_state_ = WAITING;
		enable_ = false;
		setScale(0, 0, 0);
	}



    
}