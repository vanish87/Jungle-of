#include "WindGenerator.h"

namespace Jungle
{
	WindGenerator::WindGenerator(string file_name)
	{
		enabled_ = false;
	}


	WindGenerator::~WindGenerator(void)
	{
	}

	void WindGenerator::Init()
	{
		//min_ = GetConfig("min.pex");
		//max_ = GetConfig("max.pex");

		emitter_.loadFromXml("UI/min.pex");
        emitter2_.loadFromXml("UI/min.pex");
	}

	void WindGenerator::Update( float t, float min, float max , ofVec3f l_hand_pos, ofVec3f r_hand_pos)
	{
		if(enabled_)
		{			
			//config_ = LerpConfig(t, min, max, min_, max_);
			//config_.sourcePosition.x = hand_pos.x;
			//config_.sourcePosition.y = hand_pos.y;
			//SetConfig(emitter_, config_);
			emitter_.sourcePosition.x = l_hand_pos.x;
			emitter_.sourcePosition.y = l_hand_pos.y;
			emitter_.update();
            
            emitter2_.sourcePosition.x = r_hand_pos.x;
			emitter2_.sourcePosition.y = r_hand_pos.y;
			emitter2_.update();
            
            if((l_hand_pos-l_pre_hand_pos_) != ofVec3f(0, 0, 0))
            {
                ofVec3f dir = (l_hand_pos-r_pre_hand_pos_).normalize();
                dir.x = -dir.x;
                emitter_.angle = acos(ofVec3f(1,0,0).dot(dir)) * 180/3.14;
                
                if(dir.y > 0)
                {
                    emitter_.angle = 360 - emitter_.angle;
                    
                }
            }
            
            
            if((r_hand_pos-r_pre_hand_pos_) != ofVec3f(0, 0, 0))
            {
                ofVec3f dir = (r_hand_pos-r_pre_hand_pos_).normalize();
                dir.x = -dir.x;
                emitter2_.angle = acos(ofVec3f(1,0,0).dot(dir)) * 180/3.14;
                
                if(dir.y > 0)
                {
                    emitter2_.angle = 360 - emitter2_.angle;
                    
                }
            }
            
            
            l_pre_hand_pos_ = l_hand_pos;
            r_pre_hand_pos_ = r_hand_pos;
		}
	}

	void WindGenerator::Draw()
	{
		if(enabled_)
		{
			emitter_.draw(0,0);
            emitter2_.draw(0,0);
            
		}
	}

	

	void WindGenerator::Enable( bool enable, ofVec3f hand_pos)
	{
		enabled_ = enable;
	}

	bool WindGenerator::Enabled()
	{
		return enabled_;
	}

	WindGenerator::ParticleConfig WindGenerator::GetConfig( string file_name )
	{
		ofx3DParticleEmitter emitter;
		if(!emitter.loadFromXml(file_name))
			 ofLog( OF_LOG_ERROR, "WindGenerator::GetConfig() - failed to load emitter config" );

		ParticleConfig ret;
		ret.emitterType = emitter.emitterType;

		ret.sourcePosition.x = emitter.sourcePosition.x;
		ret.sourcePosition.y = emitter.sourcePosition.y;
		ret.sourcePosition.z = emitter.sourcePosition.z;

		ret.sourcePositionVariance.x = emitter.sourcePositionVariance.x;
		ret.sourcePositionVariance.y = emitter.sourcePositionVariance.y;
		ret.sourcePositionVariance.z = emitter.sourcePositionVariance.z;

		ret.angle = emitter.angle;
		ret.angleVariance = emitter.angleVariance;								
		ret.speed = emitter.speed;
		ret.speedVariance =emitter.speedVariance;	
		ret.radialAcceleration = emitter.radialAcceleration;
		ret.tangentialAcceleration = emitter.tangentialAcceleration;
		ret.radialAccelVariance = emitter.radialAccelVariance;
		ret.tangentialAccelVariance = emitter.tangentialAccelVariance;

		ret.gravity.x = emitter.gravity.x;
		ret.gravity.y = emitter.gravity.y;
		ret.gravity.z = emitter.gravity.z;

		ret.particleLifespan = emitter.particleLifespan;
		ret.particleLifespanVariance = emitter.particleLifespanVariance;	

		ret.startColor.red = emitter.startColor.red;
		ret.startColor.green = emitter.startColor.green;
		ret.startColor.blue = emitter.startColor.blue;
		ret.startColor.alpha = emitter.startColor.alpha;

		ret.startColorVariance.red = emitter.startColorVariance.red;
		ret.startColorVariance.green = emitter.startColorVariance.green;
		ret.startColorVariance.blue = emitter.startColorVariance.blue;
		ret.startColorVariance.alpha = emitter.startColorVariance.alpha;

		ret.finishColor.red = emitter.finishColor.red;
		ret.finishColor.green = emitter.finishColor.green;
		ret.finishColor.blue = emitter.finishColor.blue;
		ret.finishColor.alpha = emitter.finishColor.alpha;
		ret.finishColorVariance.red = emitter.finishColorVariance.red;
		ret.finishColorVariance.green = emitter.finishColorVariance.green;
		ret.finishColorVariance.blue = emitter.finishColorVariance.blue;
		ret.finishColorVariance.alpha = emitter.finishColorVariance.alpha;
		ret.startParticleSize = emitter.startParticleSize;
		ret.startParticleSizeVariance = emitter.startParticleSizeVariance;
		ret.finishParticleSize = emitter.finishParticleSize;
		ret.finishParticleSizeVariance = emitter.finishParticleSizeVariance;
		ret.maxParticles = emitter.maxParticles;
		ret.particleCount = emitter.particleCount;
		ret.duration = emitter.duration;

		ret.blendFuncSource = emitter.blendFuncSource;
		ret.blendFuncDestination = emitter.blendFuncDestination;

		ret.maxRadius = emitter.maxRadius;
		ret.maxRadiusVariance = emitter.maxRadiusVariance;
		ret.radiusSpeed = emitter.radiusSpeed;
		ret.minRadius = emitter.minRadius;
		ret.rotatePerSecond = emitter.rotatePerSecond;
		ret.rotatePerSecondVariance = emitter.rotatePerSecondVariance;

		return ret;
	}

	WindGenerator::ParticleConfig WindGenerator::LerpConfig(float t, float min, float max, ParticleConfig& min_config, ParticleConfig& max_config)
	{

		float percent = (t-min)/ (max - min);

		ParticleConfig ret;
		ret.emitterType = min_.emitterType;

		ret.sourcePosition.x = ofLerp(min_config.sourcePosition.x, max_config.sourcePosition.x, percent);
		ret.sourcePosition.y = ofLerp(min_config.sourcePosition.y, max_config.sourcePosition.y, percent);
		ret.sourcePosition.z = ofLerp(min_config.sourcePosition.z, max_config.sourcePosition.z, percent);

		ret.sourcePositionVariance.x = ofLerp(min_config.sourcePositionVariance.x, max_config.sourcePositionVariance.x , percent);
		ret.sourcePositionVariance.y = ofLerp(min_config.sourcePositionVariance.y, max_config.sourcePositionVariance.y , percent);
		ret.sourcePositionVariance.z = ofLerp(min_config.sourcePositionVariance.z, max_config.sourcePositionVariance.z , percent);

		ret.angle = ofLerp(min_config.angle, max_config.angle , percent);
		ret.angleVariance = ofLerp(min_config.angleVariance, max_config.angleVariance , percent);								
		ret.speed = ofLerp(min_config.speed, max_config.speed , percent);
		ret.speedVariance = ofLerp(min_config.speedVariance, max_config.speedVariance , percent);	
		ret.radialAcceleration = ofLerp(min_config.radialAcceleration, max_config.radialAcceleration , percent);
		ret.tangentialAcceleration = ofLerp(min_config.tangentialAcceleration, max_config.tangentialAcceleration , percent);
		ret.radialAccelVariance = ofLerp(min_config.radialAccelVariance, max_config.radialAccelVariance , percent);
		ret.tangentialAccelVariance = ofLerp(min_config.tangentialAccelVariance ,max_config.tangentialAccelVariance , percent);

		ret.gravity.x = ofLerp(min_config.gravity.x, max_config.gravity.x , percent);
		ret.gravity.y = ofLerp(min_config.gravity.y, max_config.gravity.y , percent);
		ret.gravity.z = ofLerp(min_config.gravity.z, max_config.gravity.z , percent);

		ret.particleLifespan = ofLerp(min_config.particleLifespan, max_config.particleLifespan , percent);
		ret.particleLifespanVariance = ofLerp(min_config.particleLifespanVariance, max_config.particleLifespanVariance , percent);	

		ret.startColor.red = ofLerp(min_config.startColor.red, max_config.startColor.red , percent);
		ret.startColor.green = ofLerp(min_config.startColor.green, max_config.startColor.green , percent);
		ret.startColor.blue = ofLerp(min_config.startColor.blue, max_config.startColor.blue , percent);
		ret.startColor.alpha = ofLerp(min_config.startColor.alpha, max_config.startColor.alpha , percent);

		ret.startColorVariance.red = ofLerp(min_config.startColorVariance.red, max_config.startColorVariance.red , percent);
		ret.startColorVariance.green = ofLerp(min_config.startColorVariance.green, max_config.startColorVariance.green , percent);
		ret.startColorVariance.blue = ofLerp(min_config.startColorVariance.blue, max_config.startColorVariance.blue , percent);
		ret.startColorVariance.alpha = ofLerp(min_config.startColorVariance.alpha, max_config.startColorVariance.alpha , percent);

		ret.finishColor.red = ofLerp(min_config.finishColor.red, max_config.finishColor.red , percent);
		ret.finishColor.green = ofLerp(min_config.finishColor.green, max_config.finishColor.green , percent);
		ret.finishColor.blue = ofLerp(min_config.finishColor.blue, max_config.finishColor.blue , percent);
		ret.finishColor.alpha = ofLerp(min_config.finishColor.alpha, max_config.finishColor.alpha , percent);
		ret.finishColorVariance.red = ofLerp(min_config.finishColorVariance.red, max_config.finishColorVariance.red , percent);
		ret.finishColorVariance.green = ofLerp(min_config.finishColorVariance.green, max_config.finishColorVariance.green , percent);
		ret.finishColorVariance.blue = ofLerp(min_config.finishColorVariance.blue, max_config.finishColorVariance.blue , percent);
		ret.finishColorVariance.alpha = ofLerp(min_config.finishColorVariance.alpha, max_config.finishColorVariance.alpha , percent);
		ret.startParticleSize = ofLerp(min_config.startParticleSize, max_config.startParticleSize , percent);
		ret.startParticleSizeVariance = ofLerp(min_config.startParticleSizeVariance, max_config.startParticleSizeVariance , percent);
		ret.finishParticleSize = ofLerp(min_config.finishParticleSize, max_config.finishParticleSize , percent);
		ret.finishParticleSizeVariance = ofLerp(min_config.finishParticleSizeVariance, max_config.finishParticleSizeVariance , percent);
		ret.maxParticles = ofLerp(min_config.maxParticles, max_config.maxParticles , percent);
		ret.particleCount = ofLerp(min_config.particleCount, max_config.particleCount , percent);
		ret.duration = ofLerp(min_config.duration, max_config.duration , percent);

		ret.blendFuncSource = ofLerp(min_config.blendFuncSource, max_config.blendFuncSource , percent);
		ret.blendFuncDestination = ofLerp(min_config.blendFuncDestination, max_config.blendFuncDestination , percent);

		ret.maxRadius = ofLerp(min_config.maxRadius , max_config.maxRadius , percent);
		ret.maxRadiusVariance = ofLerp(min_config.maxRadiusVariance, max_config.maxRadiusVariance , percent);
		ret.radiusSpeed = ofLerp(min_config.radiusSpeed, max_config.radiusSpeed , percent);
		ret.minRadius = ofLerp(min_config.minRadius, max_config.minRadius , percent);
		ret.rotatePerSecond = ofLerp(min_config.rotatePerSecond, max_config.rotatePerSecond , percent);
		ret.rotatePerSecondVariance = ofLerp(min_config.rotatePerSecondVariance, max_config.rotatePerSecondVariance , percent);

		return ret;
	}

	void WindGenerator::SetConfig( ofx3DParticleEmitter& emitter , ParticleConfig& config)
	{
		emitter.emitterType = config.emitterType;

		emitter.sourcePosition.x = config.sourcePosition.x;
		emitter.sourcePosition.y = config.sourcePosition.y;
		emitter.sourcePosition.z = config.sourcePosition.z;

		emitter.sourcePositionVariance.x = config.sourcePositionVariance.x;
		emitter.sourcePositionVariance.y = config.sourcePositionVariance.y;
		emitter.sourcePositionVariance.z = config.sourcePositionVariance.z;

		emitter.angle = config.angle;
		emitter.angleVariance = config.angleVariance;								
		emitter.speed = config.speed;
		emitter.speedVariance =config.speedVariance;	
		emitter.radialAcceleration = config.radialAcceleration;
		emitter.tangentialAcceleration = config.tangentialAcceleration;
		emitter.radialAccelVariance = config.radialAccelVariance;
		emitter.tangentialAccelVariance = config.tangentialAccelVariance;

		emitter.gravity.x = config.gravity.x;
		emitter.gravity.y = config.gravity.y;
		emitter.gravity.z = config.gravity.z;

		emitter.particleLifespan = config.particleLifespan;
		emitter.particleLifespanVariance = config.particleLifespanVariance;	

		emitter.startColor.red = config.startColor.red;
		emitter.startColor.green = config.startColor.green;
		emitter.startColor.blue = config.startColor.blue;
		emitter.startColor.alpha = config.startColor.alpha;

		emitter.startColorVariance.red = config.startColorVariance.red;
		emitter.startColorVariance.green = config.startColorVariance.green;
		emitter.startColorVariance.blue = config.startColorVariance.blue;
		emitter.startColorVariance.alpha = config.startColorVariance.alpha;

		emitter.finishColor.red = config.finishColor.red;
		emitter.finishColor.green = config.finishColor.green;
		emitter.finishColor.blue = config.finishColor.blue;
		emitter.finishColor.alpha = config.finishColor.alpha;
		emitter.finishColorVariance.red = config.finishColorVariance.red;
		emitter.finishColorVariance.green = config.finishColorVariance.green;
		emitter.finishColorVariance.blue = config.finishColorVariance.blue;
		emitter.finishColorVariance.alpha = config.finishColorVariance.alpha;
		emitter.startParticleSize = config.startParticleSize;
		emitter.startParticleSizeVariance = config.startParticleSizeVariance;
		emitter.finishParticleSize = config.finishParticleSize;
		emitter.finishParticleSizeVariance = config.finishParticleSizeVariance;
		//emitter.maxParticles = config.maxParticles;
		//emitter.particleCount = config.particleCount;
		emitter.duration = config.duration;

		emitter.blendFuncSource = config.blendFuncSource;
		emitter.blendFuncDestination = config.blendFuncDestination;

		emitter.maxRadius = config.maxRadius;
		emitter.maxRadiusVariance = config.maxRadiusVariance;
		emitter.radiusSpeed = config.radiusSpeed;
		emitter.minRadius = config.minRadius;
		emitter.rotatePerSecond = config.rotatePerSecond;
		emitter.rotatePerSecondVariance = config.rotatePerSecondVariance;
	}


}