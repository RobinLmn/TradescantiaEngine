#pragma once
#include "Core/Core.h"
#include "Systems/System.h"
#include "Scene/Entity.h"

namespace TradescantiaEngine
{
	class ParticleSystem : public System
	{
	public:
		ParticleSystem() = default;
		virtual ~ParticleSystem();

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
	};
}
