#include "Mushroom.h"


namespace Jungle
{
	Mushroom::Mushroom(void)
		: Flower()
	{
		sounds_[0].loadSound("audio/mushroom-sounds.mp3");
		sounds_[1].loadSound("audio/mushroom-sounds.mp3");
		sounds_[2].loadSound("audio/mushroom-sounds.mp3");
		sounds_[3].loadSound("audio/mushroom-sounds.mp3");
	}


	Mushroom::~Mushroom(void)
	{
	}

	void Mushroom::Update( float frame_time )
	{
		if(enable_ && flower_state_ != WAITING)
		{            
			time_ +=frame_time;
		}
		ofVec3f scale = getScale();
		switch (flower_state_)
		{
		case GROWING:
			if(scale.x < max_scale_)
			{
				scale += scale_speed_;
			}
			if(time_ > staying_time_)
			{
				flower_state_ = DISAPPEARING;
				org_pos_ = pos;
				time_=0;			
			}
			break;
		case DISAPPEARING:
			if(scale.x > 0)
				scale -= scale_speed_;
			else
			{
				scale = ofVec3f(0, 0, 0);
				pos = org_pos_;
				flower_state_ = WAITING;
				time_ = 0;
			}
			break;
		default:
			break;
		}            
		setScale(scale.x, scale.y, scale.z);      
	}

	bool Mushroom::Collided( ofVec3f pos )
	{
		int h_ = ofGetWindowHeight();
		ofVec3f bt_pos = pos;
		bt_pos.z = 0;
		bt_pos.y = h_-bt_pos.y;
		ofVec3f mh_pos = ofVec3f(getPosition().x, getPosition().y, 0);
		if( (bt_pos - mh_pos).length() < collide_size_)
			return true;
		else
		{
			return false;
		}
	}

	void Mushroom::Triggering( bool trigger )
	{
		if(!enable_) enable_ = true;
		if(trigger)
		{
			if(flower_state_ == WAITING)
			{
				//play sound here
				int index = ofRandom(0,4);
				if (!sounds_[index].getIsPlaying())
				{
					sounds_[index].play();
					sounds_[index].setSpeed(pitch_);
				}
				flower_state_ = GROWING;
				time_ = 0;
			}			
			else
			if(flower_state_ == GROWING)
					time_ = 0;
		}
	}
    
    void Mushroom::Reset()
    {
        time_ = 0;
		flower_state_ = WAITING;
		enable_ = false;
		setScale(0, 0, 0);
    }

}
