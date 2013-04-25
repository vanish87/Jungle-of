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
    : flower_radius_(3), flower_collided_(false), color_(255,255,255), max_scale_(0.008)
    {
        setScale(0, 0, 0);
		//triggering_circle_.loadImage("");
    };
    Flower::~Flower(void)
    {
    }
    
    void Flower::Draw()
    {


		ofVec3f scale = getScale();
		if(scale.x < max_scale_)
		{
			scale += 0.0001;
			setScale(scale.x, scale.y, scale.z);
		}
        ofSetColor(color_.r, color_.g, color_.b);
        drawFaces();
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


    
}