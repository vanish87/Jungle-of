#include "SceneModel.h"
#include "JungleApp.h"

namespace Jungle
{
	SceneModel::SceneModel(void)
		:enable_(false)
	{
	}


	SceneModel::~SceneModel(void)
	{
	}

	bool SceneModel::Enabled()
	{
		return enable_;
	}

	void SceneModel::Enable( bool enable )
	{
		enable_ = enable;
	}

	void SceneModel::AddToScene()
	{
		JungleApp::SceneManagerInstance().AddToScene(this);
	}

	void SceneModel::Update( float frame_time )
	{

	}

}
