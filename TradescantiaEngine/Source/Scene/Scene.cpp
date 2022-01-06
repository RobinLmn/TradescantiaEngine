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
		ZoneScoped
		BufferLayout layout =
		{
			{TradescantiaEngine::ShaderDataType::Float3, "aPosition"}
		};

		_ParticleBuffer.reset(Buffer::Create(_Particles.data(), sizeof(Particle) * _Particles.size()));
		 
		float vertices[] = { 0.f, 0.f, 0.f };

		_VertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Layout = layout;
		_VertexArray->AddVertexBuffer(vertexBuffer);

		_Shader.reset(Shader::Create("Content/VertexShader.vs", "Content/FragmentShader.fs"));
	}

	void Scene::Render()
	{
		ZoneScoped
		_ParticleBuffer->Reset(_Particles.data(), sizeof(Particle) * _Particles.size());
		TradescantiaEngine::Renderer::Submit(_Shader, _ParticleBuffer, _VertexArray, _Particles.size());
	}
}
