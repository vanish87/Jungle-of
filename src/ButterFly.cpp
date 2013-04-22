#include "ButterFly.h"

namespace Jungle
{
	ButterFly::ButterFly(void)
	{
		butterfly_pos_.set(0, 20,28);
		butterfly_vel_.set(0, 0, 0);
		butterfly_radius_ = 50;
		butterfly_mass_ = 1;
        
        animation_time_ = 0;
        
        loadModel("Environment/Yellow_Butterfly_1.dae");
        setPosition(butterfly_pos_.x,butterfly_pos_.y,butterfly_pos_.z);
		setRotation(0, 150, 1, 0, 0);
        setScale(0.1, 0.1, 0.1);
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
        acc.y = - acc.y;
		butterfly_vel_ += acc *0.1;
		if(butterfly_vel_ != ofVec3f(0,0,0))
		{
			butterfly_vel_ += -butterfly_vel_.getNormalized() *0.01;
			if(butterfly_vel_.x < 0.1 && butterfly_vel_.x > -0.1)
				butterfly_vel_.x = 0;
			if (butterfly_vel_.y < 0.1 && butterfly_vel_.y > -0.1)
				butterfly_vel_.y = 0;
		}
		//butterfly_pos_ +=butterfly_vel_;

		butterfly_pos_.x = ofClamp(butterfly_pos_.x, min_range_.x, max_range_.x);
		butterfly_pos_.y = ofClamp(butterfly_pos_.y, min_range_.y, max_range_.y);

		setPosition(butterfly_pos_.x, butterfly_pos_.y, butterfly_pos_.z);
        
        //update animation
        animation_time_ += ofGetLastFrameTime()/24.0f;
		if( animation_time_ > 14.0f/360.0f )
		{
			animation_time_ = 0;
		}
		setAnimation(0);
		setNormalizedTime(animation_time_);

	}
    
    void ButterFly::SetRange(ofVec3f max, ofVec3f min)
    {
        max_range_ = max;
        min_range_ = min;
    }

}
