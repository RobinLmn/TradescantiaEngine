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

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			GetRendererAPI().DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI& GetRendererAPI() { static OpenGLRendererAPI rendererAPI; return rendererAPI; }
	};
}