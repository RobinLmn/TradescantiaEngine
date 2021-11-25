#include "tscpch.h"
#include "ParticleSystem.h"
#include "Entities/Particle.h"
#include "Renderer/Renderer.h"

#include <glm/gtc/random.hpp>

namespace TradescantiaEngine
{
	ParticleSystem::ParticleSystem()
	{
		TradescantiaEngine::BufferLayout layout =
		{
			{TradescantiaEngine::ShaderDataType::Float3, "a_Position"},
			{TradescantiaEngine::ShaderDataType::Float3, "a_Color"},
		};

		_VertexArray.reset(TradescantiaEngine::VertexArray::Create());

		const int size = 26000;
		Particle* _Particles[size];

		int min = -10;
		int max = 10;
		int dist = max - min;
		int r = 10;

		for (int i = 0; i < size - 5000; i++)
		{
			float x = glm::gaussRand(0.0f, 0.1f) * 8.0f;
			float y = glm::gaussRand(0.0f, 0.2f) * 0.2f;
			float z = glm::gaussRand(0.0f, 0.1f) * 8.0f;

			_Particles[i] = new Particle();
			_Particles[i]->Position = glm::vec3(x, y, z);
			float brightness = std::rand() / static_cast<float>(RAND_MAX);
			_Particles[i]->Color = glm::vec3(brightness, 0.5f, 0.8f);
		}


		for (int i = size - 5000; i < size; i++)
		{
			float x = glm::gaussRand(0.0f, 0.1f) * 2.f;
			float y = glm::gaussRand(0.0f, 0.2f) * 0.2f;
			float z = glm::gaussRand(0.0f, 0.1f) * 2.f;

			_Particles[i] = new Particle();
			_Particles[i]->Position = glm::vec3(x, y, z);
			float brightness = std::rand() / static_cast<float>(RAND_MAX) + 0.3;
			_Particles[i]->Color = glm::vec3(1.0f, 0.7f, brightness);
		}

		float vertices[size * 6];

		for (int i = 0, j = 0; i < size * 6; i += 6, j++)
		{
			vertices[i] = _Particles[j]->Position.x;
			vertices[i + 1] = _Particles[j]->Position.y;
			vertices[i + 2] = _Particles[j]->Position.z;
			vertices[i + 3] = _Particles[j]->Color.r;
			vertices[i + 4] = _Particles[j]->Color.g;
			vertices[i + 5] = _Particles[j]->Color.b;
		}

		std::shared_ptr<TradescantiaEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(TradescantiaEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		vertexBuffer->Layout = layout;
		_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[size];
		for (int i = 0; i < size; i++)
		{
			indices[i] = i;
		}

		std::shared_ptr<TradescantiaEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(TradescantiaEngine::IndexBuffer::Create(indices, sizeof(indices)));
		_VertexArray->SetIndexBuffer(indexBuffer);

		_Shader.reset(
			TradescantiaEngine::Shader::Create("C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/VertexShader.vs",
				"C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/FragmentShader.fs"));
	}

	void ParticleSystem::Update(float deltaTime)
	{
		TradescantiaEngine::Renderer::Submit(_Shader, _VertexArray);
	}
}