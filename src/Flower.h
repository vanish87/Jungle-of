#ifndef FLOWER_H_
#define FLOWER_H_

#pragma once
#include "SceneModel.h"

namespace Jungle {
    class Flower : public SceneModel
    {
    public:
        Flower(void);
        ~Flower(void);
        
        void Draw();
        void SetMaxScale(float scale);
        
    public:
        float flower_radius_;
		bool flower_collided_;
        ofColor color_;
        
        float max_scale_;
    };
}


#endif
