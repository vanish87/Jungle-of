#include "ButterFly.h"

namespace Jungle
{
	ButterFly::ButterFly(void)
	{
	}


	ButterFly::~ButterFly(void)
	{
	}

	void ButterFly::SetTexture( string texture_name )
	{
		//TODO: load all texture at first
		//TODO: check same name
		ofxAssimpMeshHelper* mesh = &this->modelMeshes[0];
		ofLoadImage(mesh->texture,texture_name);
	}

}
