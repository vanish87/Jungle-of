#include "CRSpline.h"
#include "ofMath.h"

namespace Jungle {
    CRSpline::CRSpline(void)
    {
        tau_ = 0.5;
		geo_matrix_ = ofMatrix4x4(0		, 1		, 0			, 0		,
								  -tau_ , 0		, tau_		, 0		,
								  2*tau_, tau_-3, 3- 2*tau_ , -tau_	,
								  -tau_	, 2-tau_, tau_-2	, tau_	);
    };
    CRSpline::~CRSpline(void)
    {
    }

	ofVec3f CRSpline::GetPos( ofVec3f p0, ofVec3f p1, ofVec3f p2, ofVec3f p3, float t )
	{
		t = ofClamp(t, 0, 1);
		ofVec3f ret;
		ofVec4f cx = geo_matrix_ * ofVec4f(p0.x, p1.x, p2.x, p3.x); 
		ret.x = CubicFun(t, cx);
		cx = geo_matrix_ * ofVec4f(p0.y, p1.y, p2.y, p3.y); 
		ret.y = CubicFun(t, cx);
		cx = geo_matrix_ * ofVec4f(p0.z, p1.z, p2.z, p3.z); 
		ret.z = CubicFun(t, cx);
		return ret;

	}

	float CRSpline::CubicFun( float u, ofVec4f c)
	{
		return c.x + c.y * u + c.z * u*u + c.w * u*u*u;
	}


    
    
}