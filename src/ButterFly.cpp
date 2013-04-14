#include "ButterFly.h"

namespace Jungle
{
	ButterFly::ButterFly(void)
	{
		butterfly_pos_.set(350, 350,0);
		butterfly_vel_.set(0, 0, 0);
		butterfly_radius_ = 50;
		butterfly_mass_ = 1;	
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

	void ButterFly::Update( float frame_time )
	{
		ofVec3f acc = butterfly_force_ / butterfly_mass_;
		butterfly_vel_ += acc;
		if(butterfly_vel_ != ofVec3f(0,0,0))
		{
			butterfly_vel_ += -butterfly_vel_.getNormalized() *0.1;
			if(butterfly_vel_.x < 0.1 && butterfly_vel_.x > -0.1)
				butterfly_vel_.x = 0;
			if (butterfly_vel_.y < 0.1 && butterfly_vel_.y > -0.1)
				butterfly_vel_.y = 0;
		}
		butterfly_pos_ +=butterfly_vel_;

		butterfly_pos_.x = ofClamp(butterfly_pos_.x, 0, ofGetWindowWidth());
		butterfly_pos_.y = ofClamp(butterfly_pos_.y, 0, ofGetWindowHeight());

		setPosition(butterfly_pos_.x, butterfly_pos_.y, butterfly_pos_.z);
	}

}
