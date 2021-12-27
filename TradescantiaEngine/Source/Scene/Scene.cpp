#include "tscpch.h"
#include "Scene.h"
#include "Renderer/Renderer.h"

namespace TradescantiaEngine
{
	void Scene::AddParticles(Particle* particles, const int count)
	{ 
		_Particles = particles;
		_Count = count;
	}

	void Scene::StartScene()
	{
		BufferLayout layout =
		{
			{TradescantiaEngine::ShaderDataType::Float3, "a_Position"},
			{TradescantiaEngine::ShaderDataType::Float3, "a_Color"},
		};
		 
		_Vertices = new float[_Count * 6];

		for (int i = 0, j = 0; i < _Count * 6; i += 6, j++)
		{
			_Vertices[i] = _Particles[j].Position.x;
			_Vertices[i + 1] = _Particles[j].Position.y;
			_Vertices[i + 2] = _Particles[j].Position.z;
			_Vertices[i + 3] = _Particles[j].Color.r;
			_Vertices[i + 4] = _Particles[j].Color.g;
			_Vertices[i + 5] = _Particles[j].Color.b;
		}

		_VertexArray.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(_Vertices, _Count * 6));
		vertexBuffer->Layout = layout;
		_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int* indices = new unsigned int[_Count];
		for (int i = 0; i < _Count; i++)
			indices[i] = i;

		std::shared_ptr<TradescantiaEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(TradescantiaEngine::IndexBuffer::Create(indices, _Count));
		_VertexArray->SetIndexBuffer(indexBuffer);

		_Shader.reset(
			TradescantiaEngine::Shader::Create("C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/VertexShader.vs",
				"C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/FragmentShader.fs"));

		delete[] indices;
	}

	Scene::~Scene()
	{
		delete[] _Particles;
		delete[] _Vertices;
	}

	void Scene::Render()
	{
		TradescantiaEngine::Renderer::Submit(_Shader, _VertexArray);
	}
}
