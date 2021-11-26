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
	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glPointSize(1);
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glEnable(GL_POINT_SPRITE);
		glDrawElements(GL_POINTS, vertexArray->GetIndexBuffer()->Count, GL_UNSIGNED_INT, nullptr);
	}
}