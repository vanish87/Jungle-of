#ifndef WIND_GENERATOR_H_
#define WIND_GENERATOR_H_

#pragma once
#include <list>
#include "WindParticle.h"


namespace Jungle
{
	class WindGenerator
	{
	public:
		WindGenerator(string file_name);
		~WindGenerator(void);

		void Init();
		void Update(ofVec3f hand_pos);
		void Draw();

		void SetParticleNum(int num);
		void SetMaxPaticle(int num);
		void SetMinPaticle(int num);

		void Enable(bool enable, ofVec3f hand_pos);
		bool Enabled();
		void AddParticle(ofVec3f hand_pos);
		ofVec3f butterfly_pos_;
		ofVec3f butterfly_force_;

	private:
		list<WindParticle> wind_particles_;

		//base para for particles
		float mass_;
		//spring para
		float x0_;
		float k_;
		float frac_para_;

		ofColor color_;

		//variance para
		//from 0 to inf
		float mass_vari_;
		float x0_vari_;
		float k_vari_;
		float frac_para_vari_;

		//distance that start lose particle
		float effect_dis_;
		//time after lose dragging
		float floating_time_;

		//particle num
		int num_particle_;
		int max_particle_;
		int min_particle_;

		//status
		bool enabled_;
	};
}

#endif

