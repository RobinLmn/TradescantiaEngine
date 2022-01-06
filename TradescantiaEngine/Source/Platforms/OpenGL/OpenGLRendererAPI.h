#pragma once
#include "Renderer/RendererAPI.h"
#include <glm/glm.hpp>

namespace TradescantiaEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawInstanced(const int count) override;
	};
}