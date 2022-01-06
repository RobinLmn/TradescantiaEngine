#include "tscpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include "OpenGLVertexArray.h"

namespace TradescantiaEngine
{
	OpenGLBuffer::OpenGLBuffer(void* data, uint32_t size)
	{
		glCreateBuffers(1, &_BufferID);
		Bind();
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &_BufferID);
	}

	void OpenGLBuffer::Bind()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _BufferID);
	}

	void OpenGLBuffer::BindBase()
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _BufferID);
	}

	void OpenGLBuffer::Unbind()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void OpenGLBuffer::UnbindBase()
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
	}

	void OpenGLBuffer::Reset(void* data, uint32_t size)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _BufferID);
		glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}


	/* --------------------------------------- VERTEX BUFFER --------------------------------------- */

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &_RendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &_RendererID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/* --------------------------------------- INDEX BUFFER --------------------------------------- */

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
	{
		glCreateBuffers(1, &_RendererID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		Count = count;
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &_RendererID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RendererID);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
