#include "tscpch.h"

#include "Engine.h"
#include "Input.h"
#include "Log.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"


namespace TradescantiaEngine 
{

	Engine* Engine::_Instance = nullptr;
	
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Engine::Engine() 
	{
		TSC_ASSERT(!_Instance, "Engine instance was already created");
		_Instance = this;
		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));

		_ImGuiLayer = new ImGuiLayer();
		PushOverlay(_ImGuiLayer);

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"}
		};

		_VertexArray.reset(VertexArray::Create());

		float vertices[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,   // bottom right
			-0.5f, -0.5f, 0.0f, 0.f, 1.0f, 1.0f,   // bottom left
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left
		};
		_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		_VertexBuffer->Layout = layout;
		_VertexArray->AddVertexBuffer(_VertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
		_VertexArray->SetIndexBuffer(_IndexBuffer);

		_SquareVertexArray.reset(VertexArray::Create());

		float squareVertices[] = {
			0.5f, 0.5f, 0.0f, 1.f, 0.2f, 0.2f,   // top right
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,   // top left
			-0.5f, -0.5f, 0.0f, 0.f, 1.0f, 1.0f,   // bottom left
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,   // bottom right
		};
		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->Layout = layout;
		_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		_Shader = std::unique_ptr<Shader>(new Shader("C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/VertexShader.vs", 
								"C:/Users/Shadow/Documents/GitHub/TradescantiaEngine/TradescantiaEngine/Content/FragmentShader.fs"));
	}

	Engine::~Engine() 
	{
	}

	bool Engine::OnWindowClose(WindowCloseEvent& e)
	{
		_Running = false;
		return true;
	}

	void Engine::OnEvent(Event& e)
	{
		EventDispatcher  dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Engine::OnWindowClose));

		for (auto it = _LayerStack.end(); it != _LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.isHandled())
				break;
		}
	}

	void Engine::PushLayer(Layer* layer)
	{
		_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Engine::PushOverlay(Layer* layer)
	{
		_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Engine::Run()
	{
		while (_Running)
		{
			_Shader->Use();

			glClearColor(1.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, _SquareVertexArray->GetIndexBuffer()->Count, GL_UNSIGNED_INT, nullptr);

			//_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, _IndexBuffer->Count, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : _LayerStack)
				layer->OnUpdate();

			_ImGuiLayer->Begin();
			for (Layer* layer : _LayerStack)
				layer->OnImGuiRender();
			_ImGuiLayer->End();

			_Window->OnUpdate();
		}
	}
}
