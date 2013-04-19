//
//  Animal.cpp
//  openNiSample007
//
//  Created by Yuan Li on 2/25/13.
//  Copyright 2013 nyu. All rights reserved.
//

#include "Flower.h"

namespace Jungle {
    Flower::Flower(void)
    : flower_radius_(3), flower_collided_(false), color_(255,255,255)
    {
        
    };
    Flower::~Flower(void)
    {
    }
    
    void Flower::Draw()
    {
		ofVec3f scale = getScale();
		if(scale.x < 0.008)
		{
			scale += 0.0001;
			setScale(scale.x, scale.y, scale.z);
		}
        ofSetColor(color_.r, color_.g, color_.b);
        drawFaces();
    }
    
    
}