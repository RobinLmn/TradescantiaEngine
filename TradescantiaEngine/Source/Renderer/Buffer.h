#pragma once

namespace TradescantiaEngine
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		uint32_t Count;

		static IndexBuffer* Create(uint32_t* vertices, uint32_t size);
	};
}