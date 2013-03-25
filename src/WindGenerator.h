#ifndef WIND_GENERATOR_H_
#define WIND_GENERATOR_H_

#pragma once
#include "ofVec3f.h"

namespace Jungle
{
	struct Particle
	{
		ofVec3f position;
		ofVec3f accelaration;
		ofVec4f color;
		ofVec4f delta_color;
	};
	class WindGenerator
	{
	public:
		WindGenerator(void);
		~WindGenerator(void);
	};
}

#endif

