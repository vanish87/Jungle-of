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
		ofVec3f GetScreenPos(ofVec3f world_pos, ofCamera& camera);
        
    public:
        float flower_radius_;
		bool flower_collided_;
        ofColor color_;
        
        float max_scale_;

		ofVec3f triggering_circle_;
    };
}


#endif
