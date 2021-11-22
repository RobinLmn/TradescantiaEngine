#include "tscpch.h"
#include "VertexArray.h"
#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace TradescantiaEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::API)
		{
		case ERendererAPI::None: TSC_ASSERT(false, "RendererAPI::None is invalid.");
		case ERendererAPI::OpenGL: return new OpenGLVertexArray();
		default: TSC_ASSERT(false, "No RendererAPI specified.");
		}

		return nullptr;
	}
}