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
    : flower_radius_(0.5), flower_collided_(false), color_(255,255,255)
    {
        
    };
    Flower::~Flower(void)
    {
    }
    
    void Flower::Draw()
    {
        ofSetColor(color_.r, color_.g, color_.b);
        drawFaces();
    }
    
    
}