#pragma once

#include "Core/Core.h"

#include "Window/Window.h"
#include "Layers/LayerStack.h"
#include "EventSystem/Events/WindowEvent.h"

namespace TradescantiaEngine {
	class TSC_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Engine& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Engine* s_Instance;
	};

	Engine* CreateEngine();
}

