#pragma once
#include "Core/Core.h"
#include "Systems/System.h"
#include "Scene/Particle.h"

namespace TradescantiaEngine
{
	class ParticleSystem : public System
	{
	public:
		ParticleSystem() = default;
		virtual ~ParticleSystem() = default;

		virtual void Init() override;
		virtual void FixedUpdate(float deltaTime) override;
	};
}