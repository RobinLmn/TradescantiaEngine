#pragma once

#include <TradescantiaEngine.h>

class ParticleSystem : public TradescantiaEngine::System
{
public:

	ParticleSystem()
		: _Camera(45.0f, 1, 1, 0.1f, 100.0f)
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

		_MousePosition = TradescantiaEngine::Input::GetMousePos();
		_CameraPosition = glm::vec3(0.f, 0.f, 40.f);

		_Shader.reset(
			TradescantiaEngine::Shader::Create("C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/VertexShader.vs",
				"C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/FragmentShader.fs"));
	}

	virtual ~ParticleSystem() = default;

	virtual void Init() override {}
	virtual void Terminate() override {}

	virtual void Update(float deltaTime) override
	{

		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_A))
			_CameraPosition -= glm::normalize(glm::cross(_Camera.GetFront(), _Camera.GetUp())) * _Camera.Speed;
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_D))
			_CameraPosition += glm::normalize(glm::cross(_Camera.GetFront(), _Camera.GetUp())) * _Camera.Speed;
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_S))
			_CameraPosition -= _Camera.Speed * _Camera.GetFront();
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_W))
			_CameraPosition += _Camera.Speed * _Camera.GetFront();

		if(TradescantiaEngine::Input::IsMouseButtonPressed(TSC_MOUSE_BUTTON_2))
		{
			_Camera.IncYaw((TradescantiaEngine::Input::GetMousePos().x - _MousePosition.x) * _Camera.Sensitivity);
			_Camera.IncPitch((_MousePosition.y - TradescantiaEngine::Input::GetMousePos().y) * 0.1f);
		}

		_MousePosition = TradescantiaEngine::Input::GetMousePos();

		_Camera.SetPosition(_CameraPosition);

		TradescantiaEngine::RenderCommand::SetClearColor({ 1.f, 1.f, 1.f, 1.f });
		TradescantiaEngine::RenderCommand::Clear();

		TradescantiaEngine::Renderer::BeginScene(_Camera);

		TradescantiaEngine::Renderer::Submit(_Shader, _VertexArray);
		TradescantiaEngine::Renderer::EndScene();
	}

	virtual void ImGuiRender() override {}
	virtual void OnEvent(TradescantiaEngine::Event& e) override {}

private:

	std::shared_ptr<TradescantiaEngine::VertexArray> _VertexArray;
	std::shared_ptr<TradescantiaEngine::Shader> _Shader;

	TradescantiaEngine::Camera _Camera;

	glm::vec3 _CameraPosition;
	glm::vec2 _MousePosition;
};
