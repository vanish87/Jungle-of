#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_


#pragma once
#include "SceneModel.h"
#include "Group.h"
#include "ofxXmlSettings.h"

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
		void AddToScene( SceneModel* scene_obj );

		bool LoadScene(string file_name);


		SceneType &GetDynamicObj();
	private:
		vector<SceneModel*> render_list_;
		vector<SceneModel*> scene_obj_list_;

		SceneType dynamic_objects_;

	private:
		SceneManager(const SceneManager & rhs);
		
	};

}

#endif

