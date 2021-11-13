#include "tscpch.h"

#include "Engine.h"
#include "Input.h"
#include "Log.h"

#include "Renderer/Shader.h"
#include "Platforms/OpenGL/OpenGLBuffer.h"


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

		glGenVertexArrays(1, &_VertexArray);
		glBindVertexArray(_VertexArray);

		float vertices[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.5f, 1.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  0.5f, 1.0f, 1.0f,  // bottom left
			 0.0f,  0.5f, 0.0f,  1.0f, 0.5f, 1.0f   // top 
		};

		unsigned int indices[3] = { 0, 1, 2 };

		_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); 

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

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

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(_VertexArray);
			glDrawElements(GL_TRIANGLES, _IndexBuffer->Count, GL_UNSIGNED_INT, nullptr);

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
