#ifndef TREE_H_
#define TREE_H_

#pragma once
#include "Flower.h"

namespace Jungle
{
	class Tree : public Flower
	{
	public:
		Tree(void);
		~Tree(void);

		virtual void Update( float frame_time );

		virtual bool Collided( ofVec3f pos );

		virtual void Triggering( bool trigger );

		virtual void Reset();

	};

}

#endif
