#pragma once

#include "Renderer/Buffer.h"

namespace TradescantiaEngine
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		virtual ~OpenGLVertexBuffer();
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t _RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		virtual ~OpenGLIndexBuffer();
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);

		virtual void Bind() override;
		virtual void Unbind() override;

	private:
		uint32_t _RendererID;
	};
}