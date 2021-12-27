#include "tscpch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLShader.h"

namespace TradescantiaEngine
{
	Shader* Shader::Create(const char* vertexPath, const char* fragmentPath)
	{
		switch (RendererAPI::GetRenderAPI())
		{
		case ERendererAPI::None: TSC_ASSERT(false, "RendererAPI::None is invalid.");
		case ERendererAPI::OpenGL: return new OpenGLShader(vertexPath, fragmentPath);
		default: TSC_ASSERT(false, "No RendererAPI specified.");
		}

		return nullptr;
	}
}