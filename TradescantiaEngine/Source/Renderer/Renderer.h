#pragma once
#include "VertexArray.h"

namespace TradescantiaEngine
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}