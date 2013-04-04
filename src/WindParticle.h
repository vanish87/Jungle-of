#ifndef WIND_PARTICLE_H_
#define WIND_PARTICLE_H_

#pragma once

#include "ofVec3f.h"
#include "ofGraphics.h"

#include "JungleParticle.h"

namespace Jungle
{
<<<<<<< HEAD
	class WindParticle : public JungleParticle
	{
	public:
		WindParticle(void);
		~WindParticle(void);


		WindParticle(ofVec3f pos);
		WindParticle(ofVec3f pos, float x0, float k, float mass, float frac, ofColor color);
		//calculate force of particle
		virtual void Simulate(float delta_time);
		//quick func to update a dragging force
		//better use AddForce
		void SetOrg(ofVec3f org_pos);

		ofVec3f pos_;
		ofVec3f pre_pos_;
		bool moving_;
		ofVec3f acc_;
		ofVec3f vel_;
		ofVec3f force_;
		float mass_;

		//spring para
		float x0_;
		float k_;
		float frac_para_;

		//property
		ofColor color_;

		float floating_time_;
	};

}

#endif
=======
public:
	WindParticle(void);
	~WindParticle(void);


	WindParticle(ofVec3f pos);
	//calculate force of particle
	void Simulate(float delta_time);
	//add a force to particle
	void AddForce(ofVec3f force);
	//quick func to update a dragging force
	//better use AddForce
	void SetOrg(ofVec3f org_pos);

	ofVec3f pos_;
	ofVec3f pre_pos_;
	bool moving_;
	ofVec3f acc_;
	ofVec3f vel_;
	ofVec3f force_;
	float mass_;

	//spring para
	float x0_;
	float k_;
	float frac_para_;

	//property
	ofColor color_;
};
>>>>>>> 4fe477b2ae426fda1da6c577b5c76ca06c9e92aa

