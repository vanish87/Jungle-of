#include "SceneManager.h"

namespace Jungle
{
	SceneManager::SceneManager(void)
	{
	}


	SceneManager::~SceneManager(void)
	{
	}

	void SceneManager::Update()
	{
		render_list_.clear();
		for(int i = 0; i < scene_obj_list_.size(); ++i)
		{
			if(scene_obj_list_[i]->Enabled())
			{
				scene_obj_list_[i]->Update(ofGetLastFrameTime());
				render_list_.push_back(scene_obj_list_[i]);
			}
		}
	}

	void SceneManager::Draw()
	{
		for(int i =0; i < render_list_.size(); ++i)
		{
			render_list_[i]->drawFaces();
		}
	}

	void SceneManager::AddToScene( SceneModel* scene_obj )
	{
		scene_obj_list_.push_back(scene_obj);
	}

}
