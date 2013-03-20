#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_


#pragma once
#include "SceneObject.h"

namespace Jungle
{
	class SceneManager
	{
	public:
		SceneManager(void);
		~SceneManager(void);

		void Update();
		//draw model for main camera only
		void Draw();
		void AddToScene( SceneObject* scene_obj );
	private:
		vector<SceneObject> render_list_;
		vector<SceneObject> scene_obj_list_;
	};

}

#endif

