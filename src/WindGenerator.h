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
		WindGenerator(void);
		~WindGenerator(void);

		void Update();
		void Draw();

		void SetParticleNum(int num);
		void SetMaxPaticle(int num);
		void SetMinPaticle(int num);

	private:
		list<WindParticle> wind_particles_;

		//base para for particles
		float mass_;
		//spring para
		float x0_;
		float k_;
		float frac_para_;

		//variance para
		float mass_vari_;
		float x0_vari_;
		float k_vari_;
		float frac_para_vari_;

		//particle num
		int num_particle_;
		int max_particle_;
		int min_particle_;
	};
}

#endif

