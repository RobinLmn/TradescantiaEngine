#pragma once
namespace TradescantiaEngine
{
	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		~GraphicsContext() {}
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
