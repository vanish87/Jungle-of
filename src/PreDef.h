#ifndef PREDEF_
#define PREDEF_

#pragma once
#include "ofConstants.h"
#include "ofVec3f.h"

namespace Jungle
{
	static const float ONE_DEGREE = 1;


	//(-8, 0, -1);
	static const ofVec3f MIN_PLAY_AREA = ofVec3f(-8, 0, -3);
	//( 8, 0,  5);
	static const ofVec3f MAX_PLAY_AREA = ofVec3f( 8, 0,  8);

	//kinect value we want to use
	//( 0, 0,  300);
	static const ofVec3f MIN_KINECT_AREA = ofVec3f( 0, 0,  300);
	//( 640, 480,  3000);
	static const ofVec3f MAX_KINECT_AREA = ofVec3f( 640, 480,  3000);
}

#endif