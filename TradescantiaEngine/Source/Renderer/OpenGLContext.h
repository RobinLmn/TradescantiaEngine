#pragma once
#include "GraphicsContext.h"

struct GLFWwindow;

namespace TradescantiaEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* _WindowHandle;
	};
}
