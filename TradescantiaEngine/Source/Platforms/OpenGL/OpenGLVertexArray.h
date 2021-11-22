#pragma once

#include "Renderer/VertexArray.h"

namespace TradescantiaEngine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray();
		OpenGLVertexArray();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const override { return _VertexBuffer; }
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return _IndexBuffer; }
		
	private:
		std::vector<std::shared_ptr<VertexBuffer>> _VertexBuffer;
		std::shared_ptr<IndexBuffer> _IndexBuffer;
		uint32_t _RendererID;
	};
}