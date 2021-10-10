#pragma once
#include "Core/Core.h"
#include "Window/Window.h"
#include "EventSystem/Events/WindowEvent.h"

namespace TradescantiaEngine {
	class TSC_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		void OnEvent(Event& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
	};

	Engine* CreateEngine();
}

