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
		std::unique_ptr<VertexBuffer> _VertexBuffer;
		std::unique_ptr<IndexBuffer> _IndexBuffer;
		std::unique_ptr<Shader> _Shader;

		LayerStack _LayerStack;
		ImGuiLayer* _ImGuiLayer;

		static Engine* _Instance;

		unsigned int _VertexArray;
	};

	Engine* CreateEngine();
}

