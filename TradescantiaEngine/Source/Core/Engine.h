#pragma once

#include "Core.h"

#include "LayerStack.h"
#include "Window.h"
#include "EventSystem/Events/WindowEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace TradescantiaEngine 
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *_Window; }
		inline static Engine& Get() { return *_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool _Running = true;

		LayerStack _LayerStack;
		ImGuiLayer* _ImGuiLayer;
		
		std::shared_ptr<Window> _Window;

		static Engine* _Instance;
	};

	Engine* CreateEngine();
}

