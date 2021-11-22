#pragma once

#include "Renderer/Buffer.h"
#include <memory>

namespace TradescantiaEngine
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> vertexBuffer) = 0;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}