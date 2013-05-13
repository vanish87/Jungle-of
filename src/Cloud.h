#ifndef CLOUD_H_
#define CLOUD_H_

#pragma once
#include "Flower.h"

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

	public:

		bool rain_;
		float max_time_;
		vector<SceneModel> droplet_;
        vector<ofVec3f> droplet_pos_;
        
    };
}


#endif
