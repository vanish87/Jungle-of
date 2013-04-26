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
		triggering_circle_.loadImage("Environment/glowing-circle-2.png");
		SetCircleSize(200);
    };
    Flower::~Flower(void)
    {
    }
    
    void Flower::Draw()
    {

		ofSetColor(color_.r, color_.g, color_.b);
		if(enable_)
		{
			ofVec3f scale = getScale();
		if(scale.x < max_scale_)
		{
			scale += scale_speed_;
			setScale(scale.x, scale.y, scale.z);
		}
		drawFaces();
		}
		else
		{
			triggering_circle_.draw(pos.x-circle_size_.x, pos.y-circle_size_.y, circle_size_.z, circle_size_.w);
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