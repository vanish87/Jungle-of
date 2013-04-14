#ifndef SCENE_OBJECT_H_
#define SCENE_OBJECT_H_

#pragma once
#include "ofxAssimpModelLoader.h"

namespace Jungle
{
	class SceneModel : public ofxAssimpModelLoader
	{
	public:
		SceneModel(void);
		~SceneModel(void);

		void AddToScene();

		bool Enabled();
		void Enable(bool enable);

		virtual void Update(float frame_time);

	protected:
		bool enable_;
	};

}

#endif

