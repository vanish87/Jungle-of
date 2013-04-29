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
    : flower_radius_(3), flower_collided_(false), color_(255,255,255), max_scale_(0.008), scale_speed_(0.001)
    {
        setScale(0, 0, 0);
		triggering_circle_.loadImage("Environment/trigger-circle.png");
		SetCircleSize(200);
        flower_state_ = HOLDING;
        
        circle_color_ = ofColor(255,255,255,255);
        
        //in seconds
        holding_time_ = 3;
        staying_time_ = 5;
        
        sounds_[0].loadSound("Audio/trigger1.mp3");
		sounds_[1].loadSound("Audio/trigger2.mp3");
		sounds_[2].loadSound("Audio/trigger3.mp3");
		sounds_[3].loadSound("Audio/trigger4.mp3");
    };
    Flower::~Flower(void)
    {
    }
    
    void Flower::SetCircleColor(ofColor color)
    {
        circle_color_ = color;
    }
    
    void Flower::Enable(bool enable)
    {
        if(flower_state_ == HOLDING)
        {
            
            enable_ = enable;
            if(enable != true)
            {
                time_ = 0;
            }
        }
        else
        if(flower_state_ == DISAPPEARING || flower_state_ == GROWING )
        {
            if(enable_ == enable && time_ > 0)
                time_ = 0;
        }
    }
    
    void Flower::Update(float frame_time)
    {
        if(enable_)
        {            
            time_ +=frame_time;
        }

        if(flower_state_ == HOLDING)
        {
                if (time_ > holding_time_)
                {
                    flower_state_ = GROWING;
                    
                    int index = ofRandom(0,4);
                    //cout<<index<<endl;
                    if (!sounds_[index].getIsPlaying())
                    {
                        sounds_[index].play();
                    }
                    
                    time_ = 0;
                }
            
        }
               
        
        
            
        if(flower_state_ == GROWING)
            if(time_ > staying_time_)
            {
                flower_state_ = DISAPPEARING;
                time_ = 0;
            }
        
        

    }
    
    void Flower::Draw()
    {

		ofSetColor(color_.r, color_.g, color_.b);
		if(enable_)
		{
			ofVec3f scale = getScale();
            switch (flower_state_)
            {
                case GROWING:
                    if(scale.x < max_scale_)
                    {
                        scale += scale_speed_;
                    }
                    break;
                case DISAPPEARING:
                    if(scale.x > scale_speed_)
                        scale -= scale_speed_;
                    else
                    {
                        flower_state_ = HOLDING;
                        enable_ = false;
                    }
                    break;
                case HOLDING:
                    //for(int i = 0; i < 5; ++i)
                    {
                        ofSetColor(circle_color_);
                        float scale = (holding_time_ - time_)/holding_time_;
                        if(time_ <= 0.1)
                            scale = 1;
                        ofPushMatrix();
                        ofTranslate(pos.x, pos.y);
                        triggering_circle_.draw(-circle_size_.x * scale, -circle_size_.y * scale,
                                                circle_size_.z * scale, circle_size_.w * scale);
                        ofPopMatrix();
                        //ofCircle(pos.x, pos.y, (circle_size_.z - 50 + i * 10) * scale);
                    }
                    break;
                default:
                    break;
            }            
            setScale(scale.x, scale.y, scale.z);
            drawFaces();
		}
		else
		{
			//triggering_circle_.draw(pos.x-circle_size_.x, pos.y-circle_size_.y, circle_size_.z, circle_size_.w);
            for(int i = 1; i < 5; ++i)
            {
               // ofSetColor(color_.r, color_.g, color_.b, color_.a * 0.1 * (5-i));
               // ofCircle(pos.x, pos.y, circle_size_.z - 50 + i * 10);
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
		circle_size_.x = size/2;
		circle_size_.y = 3*circle_size_.x/4;
	}

	void Flower::SetScaleSpeed( float speed )
	{
		scale_speed_ = speed;
	}


    
}