#pragma once
#include "VertexArray.h"
#include <glm/glm.hpp>

namespace TradescantiaEngine
{
	enum class ERendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static ERendererAPI API;
	};
}