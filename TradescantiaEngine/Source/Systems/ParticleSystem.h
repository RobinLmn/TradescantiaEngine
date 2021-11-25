#pragma once
#include "Core/Core.h"
#include "Systems/System.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace TradescantiaEngine
{
	class ParticleSystem : public System
	{
	public:
		ParticleSystem();
		virtual ~ParticleSystem() = default;

		virtual void Update(float deltaTime) override;

	private:

		std::shared_ptr<TradescantiaEngine::VertexArray> _VertexArray;
		std::shared_ptr<TradescantiaEngine::Shader> _Shader;
	};
}
