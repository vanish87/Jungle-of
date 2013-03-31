#ifndef FLOWER_H_
#define FLOWER_H_

#pragma once
#include "SceneObject.h"

namespace Jungle {
    class Flower : public SceneObject
    {
    public:
        Flower(void);
        ~Flower(void);
        
    public:
        float flower_radius_;
		bool flower_collided_;
    };
}


#endif
