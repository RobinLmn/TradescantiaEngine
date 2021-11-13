#pragma once

namespace TradescantiaEngine
{
	enum class ERendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		static ERendererAPI RendererAPI;
	};
}