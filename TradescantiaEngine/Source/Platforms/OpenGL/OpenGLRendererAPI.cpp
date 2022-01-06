#include "tscpch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>

namespace TradescantiaEngine
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawInstanced(const int count)
	{
		glEnable(GL_PROGRAM_POINT_SIZE);
		glPointSize(3);
		glDrawArraysInstanced(GL_POINTS, 0, 1, count);
	}
}