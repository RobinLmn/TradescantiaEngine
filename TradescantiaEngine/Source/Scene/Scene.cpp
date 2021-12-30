#include "tscpch.h"
#include "Scene.h"
#include "Renderer/Renderer.h"
#include "glad/glad.h"

namespace TradescantiaEngine
{
	void Scene::AddParticle(Particle& particle)
	{ 
		_Particles.emplace_back(particle);
	}

	void Scene::StartScene()
	{
		BufferLayout layout =
		{
			{TradescantiaEngine::ShaderDataType::Float3, "aPosition"}
		};

		glGenBuffers(1, &_ParticleBufferID); 
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ParticleBufferID);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Particle) * _Particles.size(), _Particles.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		 
		const size_t size = _Particles.size();

		float vertices[] = { 0.f, 0.f, 0.f };

		_VertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Layout = layout;
		_VertexArray->AddVertexBuffer(vertexBuffer);

		_Shader.reset(Shader::Create("Content/VertexShader.vs", "Content/FragmentShader.fs"));
	}

	void Scene::Render()
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _ParticleBufferID);
		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Particle) * _Particles.size(), _Particles.data(), GL_DYNAMIC_DRAW);

		TradescantiaEngine::Renderer::Submit(_Shader, _ParticleBufferID, _VertexArray, _Particles.size());
	}
}
