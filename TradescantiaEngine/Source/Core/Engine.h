#pragma once

#include "Core.h"

#include "LayerStack.h"
#include "Window.h"
#include "EventSystem/Events/WindowEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace TradescantiaEngine {

	class Shader;
	class VertexBuffer;
	class IndexBuffer;
	class VertexArray;

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

		std::shared_ptr<Window> _Window;
		std::shared_ptr<Shader> _Shader;
		std::shared_ptr<VertexArray> _VertexArray;

		LayerStack _LayerStack;
		ImGuiLayer* _ImGuiLayer;

		static Engine* _Instance;
	};

	Engine* CreateEngine();
}

