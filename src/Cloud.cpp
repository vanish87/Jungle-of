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
		triggering_time_ = 0;
		time_ = 0;
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
				flower_state_  = DISAPPEARING;
				time_ = 0;
			}
			if (triggering_time_ > 1)
			{
				flower_state_ = FALLING;
			}
			break;
		case FALLING:
			
			{
				rain_emitter_.update();
			}
			break;
		case DISAPPEARING:
			if(scale.x > max_scale_ * 0.3)
				scale -= scale_speed_;
			else
			{
				scale = ofVec3f(0, 0, 0);
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
			case WAITING:
				drawFaces();
				break;
			case FALLING:
				drawFaces();
				ofDisableLighting();
				ofEnableAlphaBlending();
				rain_emitter_.draw(0,0);
				ofEnableLighting();
				break;
			case HOLDING:
				break;
			}
		}
	}

	void Cloud::InitDroplet()
	{
		rain_emitter_.loadFromXml("UI/rain.pex");
		rain_emitter_.sourcePositionVariance.x = 100;
		rain_emitter_.sourcePositionVariance.y = 20;
		rain_emitter_.sourcePosition.x = pos.x;
		rain_emitter_.sourcePosition.y = pos.y;
		rain_emitter_.sourcePosition.z = 50;
	}
    
	void Cloud::Triggering( bool trigger )
	{
		Flower::Triggering(trigger);
		if(flower_state_ == WAITING)
			flower_state_ = GROWING;
		if(trigger)
		{
			triggering_time_ += ofGetLastFrameTime();
		}
		else
        {
			if (flower_state_ == FALLING)
			{
				flower_state_ = GROWING;
			}
			triggering_time_ = 0;
        }
	}

    
}