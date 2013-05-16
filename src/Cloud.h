#ifndef CLOUD_H_
#define CLOUD_H_

#pragma once
#include "Flower.h"
#include "ofx3DParticleEmitter.h"

namespace Jungle {
    class Cloud : public Flower
    {
    public:
        Cloud(void);
        ~Cloud(void);
        
		void InitDroplet();
        virtual void Update(float frame_time);
		virtual void Draw();

		virtual void Triggering( bool trigger );
        
        void UpdateRain();

		virtual bool IsGrowing();

		virtual void Reset();
		
		ofSoundPlayer rainsound();
		ofSoundPlayer rainend();

	public:
		ofx3DParticleEmitter rain_emitter_;
		float triggering_time_;
		float rainning_time_;
        bool triggering_;
        
    };
}


#endif
