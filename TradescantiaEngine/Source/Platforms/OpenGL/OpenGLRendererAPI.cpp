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
		glPointSize(4);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_POINT_SPRITE);
		glDrawArraysInstanced(GL_POINTS, 0, 1, count);
	}
}