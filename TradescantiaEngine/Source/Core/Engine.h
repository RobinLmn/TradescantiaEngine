#pragma once

#include "Core.h"

#include "System.h"
#include "Window.h"
#include "EventSystem/Events/WindowEvent.h"
#include "ImGui/ImGuiSystem.h"

namespace TradescantiaEngine 
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();
		void Update(float deltaTime);
		void Init();
		void Terminate();

		void OnEvent(Event& e);
		void PushSystem(System* system);

		inline Window& GetWindow() { return *_Window; }
		inline static Engine& Get() { return *_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool _Running = true;

		SystemStack _SystemStack;
		ImGuiSystem* _ImGuiSystem;
		Window* _Window;

		static Engine* _Instance;
	};

	Engine* CreateEngine();
}

