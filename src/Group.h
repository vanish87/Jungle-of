#ifndef GROUP_H_
#define GROUP_H_

#pragma once
#include "SceneModel.h"
#include "Flower.h"

namespace Jungle {

	class Group :public SceneModel
	{
	public:
		Group(string name, float staying_time, vector<Flower> models);
		~Group(void);

		virtual void Enable( bool enable );

		virtual void Update( float frame_time );

		void Draw();

		void Update( ofVec3f lhand_pos, ofVec3f rhand_pos = ofVec3f(0,0,0));

	private:

		string name_;
		float staying_time_;
		float time_;
		vector<Flower> models_;

	};

	typedef vector<Group> SceneType;
}

#endif

