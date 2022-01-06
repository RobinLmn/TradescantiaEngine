#pragma once
#include <glm/glm.hpp>
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace TradescantiaEngine
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			GetRendererAPI().SetClearColor(color);
		}

		inline static void Clear()
		{
			GetRendererAPI().Clear();
		}

		inline static void DrawInstanced(const int count)
		{
			ZoneScoped
			GetRendererAPI().DrawInstanced(count);
		}

	private:
		static RendererAPI& GetRendererAPI() { static OpenGLRendererAPI rendererAPI; return rendererAPI; }
	};
}