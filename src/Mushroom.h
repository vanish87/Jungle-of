#ifndef MUSHROOM_H_
#define MUSHROOM_H_

#pragma once
#include "Flower.h"

namespace Jungle
{
	class Mushroom : public Flower
	{
	public:
		Mushroom(void);
		~Mushroom(void);

		virtual void Update( float frame_time );

		virtual bool Collided( ofVec3f pos );

		virtual void Triggering( bool trigger );
        
        virtual void Reset();

	};

}

#endif
