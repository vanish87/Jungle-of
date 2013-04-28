#ifndef FLOWER_H_
#define FLOWER_H_

#pragma once
#include "SceneModel.h"

namespace Jungle {
    class Flower : public SceneModel
    {
        enum State
        {
            GROWING,
            DISAPPEARING
        };
    public:
        Flower(void);
        ~Flower(void);
        
        virtual void Update(float frame_time);
        void Draw();
        void SetMaxScale(float scale);
		void SetScaleSpeed(float speed);
		void SetCircleSize(float size);
		ofVec3f GetScreenPos(ofVec3f world_pos, ofCamera& camera);
        
    public:
        float flower_radius_;
		bool flower_collided_;
        ofColor color_;
        
        float max_scale_;
		float scale_speed_;

		ofImage triggering_circle_;
		ofVec4f circle_size_;
        
        float time_;
        State flower_state_;
    };
}


#endif
