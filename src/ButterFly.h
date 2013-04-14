#ifndef BUTTERFLY_H_
#define BUTTERFLY_H_

#pragma once
#include "SceneModel.h"

namespace Jungle
{
	
	class ButterFly : public SceneModel
	{
		friend class Player;
	public:
		ButterFly(void);
		~ButterFly(void);

		void SetTexture(string texture_name);

		virtual void Update( float frame_time );
        
        void SetRange(ofVec3f max, ofVec3f min);

	private:
		ofVec3f butterfly_pos_;
		ofVec3f butterfly_vel_;
		ofVec3f butterfly_force_;
		float butterfly_radius_;
		float butterfly_mass_;
        
        ofVec3f max_range_;
        ofVec3f min_range_;
        
        float animation_time_;
        
    private:
        ButterFly(const ButterFly & rhs);
	};

}

#endif

