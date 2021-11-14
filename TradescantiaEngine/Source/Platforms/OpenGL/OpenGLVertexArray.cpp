#include "tscpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace TradescantiaEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Bool: return GL_INT;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer)
	{
		glBindVertexArray(_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		for (const auto& element : vertexBuffer->Layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->Layout.GetStride(),
				(void*)element.Offset);
			index++;
		}

		_VertexBuffer.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
	{
		glBindVertexArray(_RendererID);
		indexBuffer->Bind();
		_IndexBuffer = indexBuffer;
	}
}
