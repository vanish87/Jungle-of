#include "Group.h"
#include "Flower.h"

namespace Jungle
{
	Group::Group( string name, float staying_time, vector<Flower*> models , GROUP_TYPE type)
		:name_(name), staying_time_(staying_time), time_(0), models_(models),
		type_(type), triggering_count_(0)
	{
		
	}

	Group::~Group(void)
	{
	}

	void Group::Enable( bool enable )
	{
		enable_ = enable;
	}

	void Group::Update( float frame_time )
	{
		//enable_ = false;

		triggering_count_ = 0;
		for(vector<Flower*>::iterator it = models_.begin(); it !=models_.end(); ++it)
		{
			(*it)->Update(frame_time);
 			if((*it)->IsGrowing())
 			{
				triggering_count_++;
				//enable_ = true;
 			}
		}
		/*if(time_ > staying_time_)
		{
			time_ = 0;
			enable_ = false;
		}
		
        if(enable_)
		{
//			time_ += frame_time;
//			for(vector<Flower>::iterator it = models_.begin(); it !=models_.end(); ++it)
//			{
//				it->SetGrowing();
//			}
		}
		else
		{
			for(vector<Flower*>::iterator it = models_.begin(); it !=models_.end(); ++it)
			{
				(*it)->SetDisapp();
			}
		}
         */

		//cout<<name_<<" "<<time_<<endl;
	}

	void Group::Update( ofVec3f lhand_pos, ofVec3f rhand_pos /*= ofVec3f(0,0,0)*/ )
	{
		if(enable_)
        {
            for(vector<Flower*>::iterator it = models_.begin(); it !=models_.end(); ++it)
            {
                if((*it)->Collided(lhand_pos) || (*it)->Collided(rhand_pos))
                {
                    (*it)->Triggering(true);
                }
                else
                {
                    (*it)->Triggering(false);
                }
            }
        }

	}

	void Group::Draw()
	{
		for(vector<Flower*>::iterator it = models_.begin(); it !=models_.end(); ++it)
		{
			(*it)->Draw();
		}

	}

	unsigned int Group::GetTriggeringCount()
	{
		return triggering_count_;
	}
    
    void Group::SetColor(ofColor color)
    {
        for(vector<Flower*>::iterator it = models_.begin(); it!= models_.end(); ++it)
        {
            (*it)->SetColor(color);
        }
    }

}
