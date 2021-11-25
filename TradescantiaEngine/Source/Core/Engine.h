#pragma once

#include "Core.h"

#include "Systems/System.h"
#include "Window.h"
#include "EventSystem/Events/WindowEvent.h"
#include "ImGui/ImGuiSystem.h"
#include "Systems/CameraSystem.h"

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
		CameraSystem* _CameraSystem;
		
		Window* _Window;

		static Engine* _Instance;
	};

	Engine* CreateEngine();
}

