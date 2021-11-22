#include "tscpch.h"

#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

TradescantiaEngine::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: _WindowHandle(windowHandle)
{
	TSC_CORE_ASSERT(windowHandle, "Window handle was null.");
}

TradescantiaEngine::OpenGLContext::~OpenGLContext()
{
}

void TradescantiaEngine::OpenGLContext::Init()
{
	glfwMakeContextCurrent(_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	TSC_CORE_ASSERT(status, "Failed to initialize glad.");
}

void TradescantiaEngine::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(_WindowHandle);
}
