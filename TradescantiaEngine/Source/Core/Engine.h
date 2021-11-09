#pragma once

#include "Core.h"

#include "Window/Window.h"
#include "LayerStack.h"
#include "EventSystem/Events/WindowEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace TradescantiaEngine {
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
		std::unique_ptr<Window> _Window;
		std::unique_ptr<ImGuiLayer> _ImGuiLayer;
		LayerStack _LayerStack;
		static Engine* _Instance;

		unsigned int _VertexArray, _VertexBuffer, _IndexBuffer;
	};

	Engine* CreateEngine();
}

