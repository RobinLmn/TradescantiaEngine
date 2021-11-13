#pragma once
#include "tscpch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"

namespace TradescantiaEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::RendererAPI)
		{
		case ERendererAPI::None:
			TSC_ASSERT(false, "RendererAPI::None is invalid.");
		case ERendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			TSC_ASSERT(false, "No RendererAPI specified.");
		}

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t size)
	{
		switch (Renderer::RendererAPI)
		{
		case ERendererAPI::None:
			TSC_ASSERT(false, "RendererAPI::None is invalid.");
		case ERendererAPI::OpenGL:
			return new OpenGLIndexBuffer(vertices, size);
		default:
			TSC_ASSERT(false, "No RendererAPI specified.");
		}

		return nullptr;
	}
}