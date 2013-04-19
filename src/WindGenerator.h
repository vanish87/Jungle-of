#ifndef WIND_GENERATOR_H_
#define WIND_GENERATOR_H_

#pragma once
#include "ofx3DParticleEmitter.h"


namespace Jungle
{
	
	class WindGenerator
	{
		struct ParticleConfig
		{
			int				emitterType;
			Vector3f		sourcePosition, sourcePositionVariance;			
			GLfloat			angle, angleVariance;								
			GLfloat			speed, speedVariance;	
			GLfloat			radialAcceleration, tangentialAcceleration;
			GLfloat			radialAccelVariance, tangentialAccelVariance;
			Vector3f		gravity;	
			GLfloat			particleLifespan, particleLifespanVariance;			
			Color4f			startColor, startColorVariance;						
			Color4f			finishColor, finishColorVariance;
			GLfloat			startParticleSize, startParticleSizeVariance;
			GLfloat			finishParticleSize, finishParticleSizeVariance;
			GLint			maxParticles;
			GLint			particleCount;
			GLfloat			duration;
			int				blendFuncSource, blendFuncDestination;

			// Particle ivars only used when a maxRadius value is provided.  These values are used for
			// the special purpose of creating the spinning portal emitter
			GLfloat			maxRadius;						// Max radius at which particles are drawn when rotating
			GLfloat			maxRadiusVariance;				// Variance of the maxRadius
			GLfloat			radiusSpeed;					// The speed at which a particle moves from maxRadius to minRadius
			GLfloat			minRadius;						// Radius from source below which a particle dies
			GLfloat			rotatePerSecond;				// Number of degrees to rotate a particle around the source position per second
			GLfloat			rotatePerSecondVariance;		// Variance in degrees for rotatePerSecond


			ParticleConfig& operator=(const ParticleConfig& rhs)
			{
				if (this == &rhs) return *this;

				emitterType = rhs.emitterType;

				sourcePosition.x = rhs.sourcePosition.x;
				sourcePosition.y = rhs.sourcePosition.y;
				sourcePosition.z = rhs.sourcePosition.z;

				sourcePositionVariance.x = rhs.sourcePositionVariance.x;
				sourcePositionVariance.y = rhs.sourcePositionVariance.y;
				sourcePositionVariance.z = rhs.sourcePositionVariance.z;

				angle = rhs.angle;
				angleVariance = rhs.angleVariance;								
				speed = rhs.speed;
				speedVariance =rhs.speedVariance;	
				radialAcceleration = rhs.radialAcceleration;
				tangentialAcceleration = rhs.tangentialAcceleration;
				radialAccelVariance = rhs.radialAccelVariance;
				tangentialAccelVariance = rhs.tangentialAccelVariance;

				gravity.x = rhs.gravity.x;
				gravity.y = rhs.gravity.y;
				gravity.z = rhs.gravity.z;

				particleLifespan = rhs.particleLifespan;
				particleLifespanVariance = rhs.particleLifespanVariance;	

				startColor.red = rhs.startColor.red;
				startColor.green = rhs.startColor.green;
				startColor.blue = rhs.startColor.blue;
				startColor.alpha = rhs.startColor.alpha;

				startColorVariance.red = rhs.startColorVariance.red;
				startColorVariance.green = rhs.startColorVariance.green;
				startColorVariance.blue = rhs.startColorVariance.blue;
				startColorVariance.alpha = rhs.startColorVariance.alpha;

				finishColor.red = rhs.finishColor.red;
				finishColor.green = rhs.finishColor.green;
				finishColor.blue = rhs.finishColor.blue;
				finishColor.alpha = rhs.finishColor.alpha;
				finishColorVariance.red = rhs.finishColorVariance.red;
				finishColorVariance.green = rhs.finishColorVariance.green;
				finishColorVariance.blue = rhs.finishColorVariance.blue;
				finishColorVariance.alpha = rhs.finishColorVariance.alpha;
				startParticleSize = rhs.startParticleSize;
				startParticleSizeVariance = rhs.startParticleSizeVariance;
				finishParticleSize = rhs.finishParticleSize;
				finishParticleSizeVariance = rhs.finishParticleSizeVariance;
				maxParticles = rhs.maxParticles;
				particleCount = rhs.particleCount;
				duration = rhs.duration;

				blendFuncSource = rhs.blendFuncSource;
				blendFuncDestination = rhs.blendFuncDestination;

				maxRadius = rhs.maxRadius;
				maxRadiusVariance = rhs.maxRadiusVariance;
				radiusSpeed = rhs.radiusSpeed;
				minRadius = rhs.minRadius;
				rotatePerSecond = rhs.rotatePerSecond;
				rotatePerSecondVariance = rhs.rotatePerSecondVariance;

				return *this;
			}
			ParticleConfig()
			{
				emitterType = kParticleTypeGravity;
				sourcePosition.x = sourcePosition.y = sourcePosition.z = 0.0f;
				sourcePositionVariance.x = sourcePositionVariance.y = sourcePositionVariance.z = 0.0f;
				angle = angleVariance = 0.0f;								
				speed = speedVariance = 0.0f;	
				radialAcceleration = tangentialAcceleration = 0.0f;
				radialAccelVariance = tangentialAccelVariance = 0.0f;
				gravity.x = gravity.y = gravity.z = 0.0f;
				particleLifespan = particleLifespanVariance = 0.0f;			
				startColor.red = startColor.green = startColor.blue = startColor.alpha = 1.0f;
				startColorVariance.red = startColorVariance.green = startColorVariance.blue = startColorVariance.alpha = 1.0f;
				finishColor.red = finishColor.green = finishColor.blue = finishColor.alpha = 1.0f;
				finishColorVariance.red = finishColorVariance.green = finishColorVariance.blue = finishColorVariance.alpha = 1.0f;
				startParticleSize = startParticleSizeVariance = 0.0f;
				finishParticleSize = finishParticleSizeVariance = 0.0f;
				maxParticles = 0.0f;
				particleCount = 0;
				duration = -1;

				blendFuncSource = blendFuncDestination = 0;

				maxRadius = maxRadiusVariance = radiusSpeed = minRadius = 0.0f;
				rotatePerSecond = rotatePerSecondVariance = 0.0f;
			}
			ParticleConfig(const ParticleConfig& rhs)
			{
				emitterType = rhs.emitterType;

				sourcePosition.x = rhs.sourcePosition.x;
				sourcePosition.y = rhs.sourcePosition.y;
				sourcePosition.z = rhs.sourcePosition.z;

				sourcePositionVariance.x = rhs.sourcePositionVariance.x;
				sourcePositionVariance.y = rhs.sourcePositionVariance.y;
				sourcePositionVariance.z = rhs.sourcePositionVariance.z;

				angle = rhs.angle;
				angleVariance = rhs.angleVariance;								
				speed = rhs.speed;
				speedVariance =rhs.speedVariance;	
				radialAcceleration = rhs.radialAcceleration;
				tangentialAcceleration = rhs.tangentialAcceleration;
				radialAccelVariance = rhs.radialAccelVariance;
				tangentialAccelVariance = rhs.tangentialAccelVariance;

				gravity.x = rhs.gravity.x;
				gravity.y = rhs.gravity.y;
				gravity.z = rhs.gravity.z;

				particleLifespan = rhs.particleLifespan;
				particleLifespanVariance = rhs.particleLifespanVariance;	

				startColor.red = rhs.startColor.red;
				startColor.green = rhs.startColor.green;
				startColor.blue = rhs.startColor.blue;
				startColor.alpha = rhs.startColor.alpha;

				startColorVariance.red = rhs.startColorVariance.red;
				startColorVariance.green = rhs.startColorVariance.green;
				startColorVariance.blue = rhs.startColorVariance.blue;
				startColorVariance.alpha = rhs.startColorVariance.alpha;

				finishColor.red = rhs.finishColor.red;
				finishColor.green = rhs.finishColor.green;
				finishColor.blue = rhs.finishColor.blue;
				finishColor.alpha = rhs.finishColor.alpha;
				finishColorVariance.red = rhs.finishColorVariance.red;
				finishColorVariance.green = rhs.finishColorVariance.green;
				finishColorVariance.blue = rhs.finishColorVariance.blue;
				finishColorVariance.alpha = rhs.finishColorVariance.alpha;
				startParticleSize = rhs.startParticleSize;
				startParticleSizeVariance = rhs.startParticleSizeVariance;
				finishParticleSize = rhs.finishParticleSize;
				finishParticleSizeVariance = rhs.finishParticleSizeVariance;
				maxParticles = rhs.maxParticles;
				particleCount = rhs.particleCount;
				duration = rhs.duration;

				blendFuncSource = rhs.blendFuncSource;
				blendFuncDestination = rhs.blendFuncDestination;

				maxRadius = rhs.maxRadius;
				maxRadiusVariance = rhs.maxRadiusVariance;
				radiusSpeed = rhs.radiusSpeed;
				minRadius = rhs.minRadius;
				rotatePerSecond = rhs.rotatePerSecond;
				rotatePerSecondVariance = rhs.rotatePerSecondVariance;
			}
		};
	public:
		WindGenerator(string file_name);
		~WindGenerator(void);

		void Init();
		void Update(float t, float min, float max, ofVec3f hand_pos);
		void Draw();		

		void Enable(bool enable, ofVec3f hand_pos);
		bool Enabled();

	private:
		ParticleConfig GetConfig(string file_name);
		ParticleConfig LerpConfig(float t, float min, float max, ParticleConfig& min_config, ParticleConfig& max_config);
		void SetConfig(ofx3DParticleEmitter& emitter, ParticleConfig& config);

	private:
		//status
		bool enabled_;

		ofx3DParticleEmitter emitter_;
        ofx3DParticleEmitter emitter2_;

		ParticleConfig config_;
		ParticleConfig min_;
		ParticleConfig max_;
	};
}

#endif

