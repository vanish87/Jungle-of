#ifndef BUTTERFLY_H_
#define BUTTERFLY_H_

#pragma once
#include "SceneObject.h"

namespace Jungle
{
	class ButterFly : public SceneObject
	{
	public:
		ButterFly(void);
		~ButterFly(void);

		void SetTexture(string texture_name);

	private:
	};

}

#endif

