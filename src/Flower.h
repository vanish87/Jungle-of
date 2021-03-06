#ifndef FLOWER_H_
#define FLOWER_H_

#pragma once
#include "SceneModel.h"

namespace Jungle {
    class Flower : public SceneModel
    {
	protected:
        enum State
        {
			HOLDING,
            GROWING,
			FALLING,
            DISAPPEARING,
            WAITING,
        };
    public:
        Flower(void);
        ~Flower(void);
        
        virtual void Update(float frame_time);
        virtual void Draw();
        void SetMaxScale(float scale);
		void SetScaleSpeed(float speed);
		void SetCircleSize(float size);
        void SetCircleColor(ofColor color);
		void SetCollideSize(float size);
        
        void SetFalling(bool falling);
        void SetPitch(float pitch);
        
        void SetColor(ofColor color);
		ofVec3f GetScreenPos(ofVec3f world_pos, ofCamera& camera);

		virtual bool Collided(ofVec3f pos);

		virtual bool IsGrowing();
		void SetGrowing();

		virtual void Triggering(bool trigger);
		void SetDisapp();

		virtual void Reset();
	public:
        ofColor color_;
        ofColor circle_color_;
        
        float max_scale_;
		float scale_speed_;

		ofxAssimpModelLoader triggering_circle_;
		ofVec4f circle_size_;
        
        float time_;
        float holding_time_;
        float staying_time_;
        State flower_state_;

		ofVec3f org_pos_;
        
        float collide_size_;
        ofSoundPlayer sounds_[6];
		float pitch_;
        bool falling_;
        
        float triggering_time_;
        
    };
}


#endif
