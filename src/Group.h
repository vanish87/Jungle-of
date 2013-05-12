#ifndef GROUP_H_
#define GROUP_H_

#pragma once
#include "SceneModel.h"
#include "Flower.h"

namespace Jungle {

	class Group :public SceneModel
	{
	public:
		enum GROUP_TYPE
		{
			TREE,
			LEAF,
            FRUIT,
			MUSHROOM,
            CLOUD
		};
	public:
		Group(string name, float staying_time, vector<Flower*> models, GROUP_TYPE type);
		~Group(void);

		virtual void Enable( bool enable );

		virtual void Update( float frame_time );

		void Draw();

		void Update( ofVec3f lhand_pos, ofVec3f rhand_pos = ofVec3f(0,0,0));
        
        void SetColor(ofColor color);

		GROUP_TYPE GetType(){return type_;};
		unsigned int GetTriggeringCount();
	public:

		string name_;
		GROUP_TYPE type_;
		float staying_time_;
		float time_;
		vector<Flower*> models_;
		unsigned int triggering_count_;

	};

	typedef vector<Group> SceneType;
}

#endif

