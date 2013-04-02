#include "WindGenerator.h"

namespace Jungle
{
	WindGenerator::WindGenerator(void)
	{
	}


	WindGenerator::~WindGenerator(void)
	{
	}

	void WindGenerator::Update()
	{
		list<WindParticle>::iterator itr;
		for( itr = wind_particles_.begin(); itr!= wind_particles_.end(); ++itr)
		{
			itr->Simulate(0);
		}
	}

	void WindGenerator::Draw()
	{
		list<WindParticle>::iterator itr;
		for( itr = wind_particles_.begin(); itr!= wind_particles_.end(); ++itr)
		{
			ofSetColor(itr->color_);
			ofPushMatrix();
			ofTranslate(itr->pos_.x, itr->pos_.y, 0.0f);
			ofCircle(0, 0, 3); //size of particles
			ofPopMatrix();
			ofSetColor(255, 255, 255);
		}
	}

	void WindGenerator::SetParticleNum( int num )
	{
		num_particle_ = num;
	}

	void WindGenerator::SetMaxPaticle( int num )
	{
		max_particle_ = num;
	}

	void WindGenerator::SetMinPaticle( int num )
	{
		min_particle_ = num;
	}

}