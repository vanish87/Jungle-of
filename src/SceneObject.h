#ifndef SCENE_OBJECT_H_
#define SCENE_OBJECT_H_

#pragma once
#include "ofxAssimpModelLoader.h"

namespace Jungle
{
	class SceneObject : public ofxAssimpModelLoader
	{
	public:
		SceneObject(void);
		~SceneObject(void);

		void AddToScene();

		bool Enabled();
		void Enable(bool enable);

	protected:
		bool enable_;
	};

}

#endif

