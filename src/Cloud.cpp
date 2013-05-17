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
		rainning_time_ = 0;
		triggering_time_ = 0;
		time_ = 0;
        triggering_ = false;
		
		rainsound.loadSound("audio/rainloop.mp3");
		rainend.loadSound("audio/rainloop-end.mp3");
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
			org_pos_ = pos;
			if(scale.x < max_scale_)
			{
				scale += scale_speed_;
			}

			if(time_ > staying_time_)
			{
				flower_state_  = DISAPPEARING;
				time_ = 0;
			}
			if (triggering_time_ > 0.3)
			{
				rainsound.setLoop(true);
                rainsound.play();
				flower_state_ = FALLING;
			}
			break;
		case FALLING:			
			{
                
                rainning_time_+=ofGetLastFrameTime();
				rain_emitter_.update();
			}
			break;
		case DISAPPEARING:
			{
				//scale = ofVec3f(0, 0, 0);
				flower_state_ = WAITING;
				time_ = 0;
			}
			break;
		case HOLDING:		
			if (time_ > holding_time_)
            {
				flower_state_ = GROWING;
				
                if(falling_)
                {
                    
                }
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
		if(!rain_emitter_.loadFromXml("UI/rain.pex"))
            cout<<"error"<<endl;
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
            triggering_ = true;
            triggering_time_ += ofGetLastFrameTime();
		}
		else
        {
            if(triggering_)
            {
               rainning_time_ = 0;
                triggering_ = false;
            }
			if (flower_state_ == FALLING)
			{
                if(rainning_time_ > 5)
                {
                    //stop rainning
                    if(rainsound.getIsPlaying() && rainsound.getPosition() > 0.95)
                    {
                        rainsound.setLoop(false);
                        rainend.play();
                        flower_state_ = GROWING;
                        triggering_time_ = 0;
                        rainning_time_ = 0;
                    }
                }
			}
        }
	}

	bool Cloud::IsGrowing()
	{
		if(rainning_time_ > 0)
			return true;
		else
			return false;
	}

	void Cloud::Reset()
	{
		Flower::Reset();
        if(rainsound.getIsPlaying())
        {
            rainsound.setLoop(false);
            rainend.play();
        }
		triggering_time_ = 0;
		rainning_time_ = 0;
	}

    
}