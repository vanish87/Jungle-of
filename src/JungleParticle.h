#ifndef JUNGLE_PARTICLE_H_
#define JUNGLE_PARTICLE_H_

#pragma once
#include "ofVec3f.h"
namespace Jungle
{
	class JungleParticle
	{
	public:
		JungleParticle(void);
		~JungleParticle(void);
		
		//add a force to particle
		virtual void AddForce(ofVec3f force);
		virtual void Simulate(float delta_time) = 0;

		ofVec3f acc_;
		ofVec3f vel_;
		ofVec3f force_;
		float mass_;

	};


}
#endif

