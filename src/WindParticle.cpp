#include "WindParticle.h"

namespace Jungle
{
	WindParticle::WindParticle(void)
	{
		moving_ = false;

		pos_.set(300, 300, 0);
		acc_.set(0, 0, 0);
		vel_.set(0, 0, 0);

		x0_ = 60 * ofRandom(0.5,1);
		k_ = 0.3* ofRandom(0.3,1);;
		mass_ = 5* ofRandom(0.6,1);;
		frac_para_ = 50* ofRandom(0.5,1);

	}

	WindParticle::WindParticle( ofVec3f pos )
	{
		moving_ = false;

		pos_ = pos;
		acc_.set(0, 0, 0);
		vel_.set(ofRandomf(), ofRandomf(), 0);

		x0_ = 10 * ofRandom(0.5,1);
		k_ = 0.1* ofRandom(0.3,1);
		mass_ = 10* ofRandom(0.6,1);
		frac_para_ = 10* ofRandom(0.5,1);
	}

	WindParticle::WindParticle( ofVec3f pos, float x0, float k, float mass, float frac, ofColor color)
	{
		moving_ = false;

		pos_ = pos;
		acc_.set(0, 0, 0);
		vel_.set(ofRandomf(), ofRandomf(), 0);

		x0_ = x0;
		k_ = k;
		mass_ = mass;
		frac_para_ = frac;

		color_ = color;
		floating_time_ = 0;
	}


	WindParticle::~WindParticle(void)
	{
<<<<<<< HEAD
=======
		force += frac;
		//cout<<"frac"<<endl;
>>>>>>> 4fe477b2ae426fda1da6c577b5c76ca06c9e92aa
	}

	void WindParticle::Simulate( float delta_time )
	{
		//if floating update floating time
		if(0 == k_)
		{
			floating_time_ += delta_time;
		}
		//length of spring
		float d = force_.length();
		//spring force
		float f = ofClamp(k_ * (d - x0_),0, 1000);
		ofVec3f force = f * (force_.normalize());
		//velocity dir
		ofVec3f v_dir = vel_;
		v_dir.normalize();
		//fraction dir = opposite to vel dir
		ofVec3f frac = -frac_para_ * v_dir;
		if(moving_)
		{
			force = force + frac;
			//cout<<"force +frac"<<endl;
		}
		else
		{
			force += frac;
			//cout<<"frac"<<endl;
		}

		//acceleration
		acc_ = force / mass_;
		vel_ += acc_;
		//update pos
		pos_ += vel_;

		//restrain in screen
		pos_.x = ofClamp(pos_.x, 50, 1280-50);
		pos_.y = ofClamp(pos_.y, 50, 720-50);


		//     ofDisableAlphaBlending();
		// 	ofSetColor( 0, 74, 255 );
		//     //   (0+i*5, 74+i*5, 255-i*5), (255-j*5, 226+j*5, 141+j*5) with i = 10 and j = 5
		// 
		// 	ofPushMatrix();
		// 	ofTranslate(pos_.x, pos_.y, 0.0f);
		// 	ofCircle(0, 0, 3); //size of particles
		// 	ofPopMatrix();
		//     ofSetColor(255, 255, 255);
	}

	void WindParticle::SetOrg( ofVec3f org_pos )
	{
		if(org_pos.x == pre_pos_.x && org_pos.y == pre_pos_.y)
			moving_ = false;
		else
			moving_ = true;
		force_ = org_pos - pos_;
		pre_pos_ = org_pos;
	}

<<<<<<< HEAD
=======
	//acceleration
	acc_ = force / mass_;
	vel_ += acc_;
	//update pos
	pos_ += vel_;

	//restrain in screen
	pos_.x = ofClamp(pos_.x, 50, 1280-50);
	pos_.y = ofClamp(pos_.y, 50, 720-50);


     ofDisableAlphaBlending();
 	ofSetColor( 0, 74, 255 );
     //   (0+i*5, 74+i*5, 255-i*5), (255-j*5, 226+j*5, 141+j*5) with i = 10 and j = 5
 
 	ofPushMatrix();
 	ofTranslate(pos_.x, pos_.y, 0.0f);
 	ofCircle(0, 0, 3); //size of particles
 	ofPopMatrix();
    ofSetColor(255, 255, 255);
}
>>>>>>> 4fe477b2ae426fda1da6c577b5c76ca06c9e92aa



}
