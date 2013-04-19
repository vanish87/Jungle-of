#ifndef CRSPLINES_H_
#define CRSPLINES_H_

#pragma once
#include "ofMatrix4x4.h"

namespace Jungle {
    class CRSpline 
    {
    public:
        CRSpline(void);
        ~CRSpline(void);

		//get pos between P2 and P3 with t=[0,1]
		ofVec3f GetPos(ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3, float t);
		float CubicFun(float u, ofVec4f c);
        
    public:
        float tau_;
		ofMatrix4x4 geo_matrix_;
    };
}


#endif
