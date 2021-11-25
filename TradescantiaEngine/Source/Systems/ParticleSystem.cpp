#include "tscpch.h"
#include "ParticleSystem.h"
#include "Entities/Particle.h"
#include "Renderer/Renderer.h"

namespace TradescantiaEngine
{
	ParticleSystem::ParticleSystem()
	{
		TradescantiaEngine::BufferLayout layout =
		{
			{TradescantiaEngine::ShaderDataType::Float3, "a_Position"},
			{TradescantiaEngine::ShaderDataType::Float, "a_Size"},
		};

		_VertexArray.reset(TradescantiaEngine::VertexArray::Create());

		const int size = 10000;
		Particle* _Particles[size];

		int min = -10;
		int max = 10;
		int dist = max - min;
		int r = 10;

		for (int i = 0; i < size; i++)
		{
			float x;
			float y;
			float z;

			do
			{
				x = std::rand() / static_cast<float>(RAND_MAX) * dist + min;
				y = std::rand() / static_cast<float>(RAND_MAX) * dist + min;
				z = std::rand() / static_cast<float>(RAND_MAX) * dist + min;
			} while (x * x + y * y + z * z > r * r);

			_Particles[i] = new Particle();
			_Particles[i]->Position = glm::vec3(x, y, z);
			_Particles[i]->Brightness = std::rand() / static_cast<float>(RAND_MAX);
		}

		float vertices[size * 4];

		for (int i = 0, j = 0; i < size * 4; i += 4, j++)
		{
			vertices[i] = _Particles[j]->Position.x;
			vertices[i + 1] = _Particles[j]->Position.y;
			vertices[i + 2] = _Particles[j]->Position.z;
			vertices[i + 3] = _Particles[j]->Brightness;
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