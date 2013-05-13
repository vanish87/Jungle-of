#ifndef UTILITY_H_
#define UTILITY_H_

#pragma once

namespace Jungle
{
	inline ofColor Lerp(const ofColor &start, const ofColor &end, float incr) 
	{
		ofColor color;
		color.r = ofLerp(start.r, end.r, incr);
		color.g = ofLerp(start.g, end.g, incr);
		color.b = ofLerp(start.b, end.b, incr);
		return color;
	}
}
#endif