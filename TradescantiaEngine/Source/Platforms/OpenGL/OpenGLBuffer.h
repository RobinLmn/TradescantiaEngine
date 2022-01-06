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

	class OpenGLBuffer : public Buffer
	{
	public:
		virtual ~OpenGLBuffer();
		OpenGLBuffer(void* data, uint32_t size);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void BindBase() override;
		virtual void UnbindBase() override;

		virtual void Reset(void* data, uint32_t size) override;

	private:
		uint32_t _BufferID;
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