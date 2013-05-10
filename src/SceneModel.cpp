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

	bool SceneModel::Collided( ofVec3f pos )
	{
		return false;
	}
    void SceneModel::AddTexture(string tex_name)
    {
        if(textures_.empty())
        {
            ofxAssimpMeshHelper* mesh = &this->modelMeshes[0];
            textures_.push_back(mesh->texture);
        }
        ofTexture tex;
		ofLoadImage(tex,tex_name);
        textures_.push_back(tex);
    }
    void SceneModel::Settexture(int num)
    {
        ofxAssimpMeshHelper* mesh = &this->modelMeshes[0];
        mesh->texture = textures_[num];
    }


}
