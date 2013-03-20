#include "SceneObject.h"
#include "JungleApp.h"

namespace Jungle
{
	SceneObject::SceneObject(void)
		:enable_(false)
	{
	}


	SceneObject::~SceneObject(void)
	{
	}

	bool SceneObject::Enabled()
	{
		return enable_;
	}

	void SceneObject::Enable( bool enable )
	{
		enable_ = enable;
	}

	void SceneObject::AddToScene()
	{
		JungleApp::SceneManagerInstance().AddToScene(this);
	}

}
