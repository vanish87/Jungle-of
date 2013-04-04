#include "JungleParticle.h"

namespace Jungle
{
	JungleParticle::JungleParticle(void)
	{
	}


	JungleParticle::~JungleParticle(void)
	{
	}

	void JungleParticle::AddForce(ofVec3f force)
	{
			force_ += force;
	}

}
