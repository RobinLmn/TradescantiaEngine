#include "tscpch.h"
#include "Engine.h"
#include <GLFW/glfw3.h>

namespace TradescantiaEngine 
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Engine::Engine() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));
	}

	Engine::~Engine() {}

	bool Engine::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Engine::OnEvent(Event& e)
	{
		EventDispatcher  dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Engine::OnWindowClose));
	}

	void Engine::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
