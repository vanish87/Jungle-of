#include "WindGenerator.h"

#include "ofAppRunner.h"

namespace Jungle
{
	WindGenerator::WindGenerator(string file_name)
	{
		
		x0_ = 50;
		k_ = 0.1;
		mass_ = 5;
		frac_para_ = 30;

		x0_vari_ = 1;
		k_vari_ = 1;
		mass_vari_ = 1;
		frac_para_vari_ = 1;

		effect_dis_ = 300;
		floating_time_ = 3;

		ofSetColor(255, 226, 141, 20); 

		//TODO: init max, min
		num_particle_ = 300;
		max_particle_ = 400;
		min_particle_ = 250;

		enabled_ = false;

		butterfly_pos_ = ofVec3f(1280/2,720/2,0);
		butterfly_force_.set(0.0f, 0.0f, 0.0f);
	}


	WindGenerator::~WindGenerator(void)
	{
	}

	void WindGenerator::Init()
	{
		float x0 = 0;
		float k = 0;
		float mass = 0;
		float frac_para = 0;
		for(int i = 0; i < num_particle_; ++i)
		{
			x0 = x0_ + ofRandom(-1, 1) * x0_vari_;
			k = k_+ ofRandom(-1, 1) * k_vari_;
			mass = mass_+ ofRandom(-1, 1) * mass_vari_;
			frac_para = frac_para_+ ofRandom(-1, 1) * frac_para_vari_;
			WindParticle particle(butterfly_pos_, x0, k, mass, frac_para, color_);
			wind_particles_.push_back(particle);
		}
	}
	void WindGenerator::Update(ofVec3f hand_pos)
	{
		if(enabled_)
		{
			butterfly_force_.set(0,0,0);
			list<WindParticle>::iterator itr;
			for( itr = wind_particles_.begin(); itr!= wind_particles_.end();)
			{
				//lost dragging if it too far from hand
				if(itr->pos_.distance(hand_pos) > effect_dis_ && num_particle_ > min_particle_)
					itr->k_ = 0;
				//delete it if it floating too long
				if(itr->floating_time_ > floating_time_ && num_particle_ > min_particle_)
				{
					itr = wind_particles_.erase(itr);
					num_particle_--;
				}
				else
				{
					++itr;
				}
			}
			for( itr = wind_particles_.begin(); itr!= wind_particles_.end(); ++itr)
			{
				//update rest
				itr->SetOrg(hand_pos);

				itr->Simulate(ofGetLastFrameTime());
				//butterfly bounce
				if(itr->pos_.distance(ofVec3f(1280/2,720/2,0))< 50)
				{
					ofVec3f dir = itr->pos_ - ofVec3f(1280/2,720/2,0);
					dir.normalize();

					itr->pos_ = dir*50 + ofVec3f(1280/2,720/2,0);
					//itr->AddForce(dir*100);

					ofVec3f f_dir = itr->vel_;
					f_dir.y= -f_dir.y;
					butterfly_force_ += f_dir * 0.3;
					butterfly_force_.x = ofClamp(butterfly_force_.x, -40, 40);
					butterfly_force_.y = ofClamp(butterfly_force_.y, -40, 40);
					//cout<<pos_.x<<" "<<pos_.y<<" "<<pos_.z<<endl;
				}
			}

		}

		

	}

	void WindGenerator::Draw()
	{
		if(enabled_)
		{
			ofEnableAlphaBlending();
			list<WindParticle>::iterator itr;
			for( itr = wind_particles_.begin(); itr!= wind_particles_.end(); ++itr)
			{
				ofSetColor(itr->color_.r , itr->color_.g, itr->color_.b, (1 - itr->floating_time_/floating_time_) * color_.a);
				ofPushMatrix();
				ofTranslate(itr->pos_.x, itr->pos_.y, 0.0f);
				ofCircle(0, 0, 3); //size of particles
				ofPopMatrix();
				ofSetColor(255, 255, 255);
			}

			ofDisableAlphaBlending();
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

	void WindGenerator::Enable( bool enable, ofVec3f hand_pos)
	{
		if(!enabled_ && enable)
		{
			list<WindParticle>::iterator itr;
			for( itr = wind_particles_.begin(); itr!= wind_particles_.end(); ++itr)
			{
				itr->pos_ = hand_pos;
			}
		}
		enabled_ = enable;
	}

	void WindGenerator::AddParticle(ofVec3f hand_pos)
	{
        for(int i =0 ; i < 50 ; i++)
		if(num_particle_ < max_particle_)
		{
			float x0 = 0;
			float k = 0;
			float mass = 0;
			float frac_para = 0;
			x0 = x0_ + ofRandom(-1, 1) * x0_vari_;
			k = k_+ ofRandom(-1, 1) * k_vari_;
			mass = mass_+ ofRandom(-1, 1) * mass_vari_;
			frac_para = frac_para_+ ofRandom(-1, 1) * frac_para_vari_;
			WindParticle particle(hand_pos, x0, k, mass, frac_para, color_);
			wind_particles_.push_back(particle);
			num_particle_++;
		}
	}

	bool WindGenerator::Enabled()
	{
		return enabled_;
	}



}