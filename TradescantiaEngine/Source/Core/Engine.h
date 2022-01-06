#pragma once

#include "Core.h"

#include "Systems/System.h"
#include "Window.h"
#include "EventSystem/Events/WindowEvent.h"
#include "Systems/ImGuiSystem.h"
#include "Systems/CameraSystem.h"

namespace TradescantiaEngine 
{
	class Engine
	{
	private:
		Engine() = default;

		bool OnWindowClose(WindowCloseEvent& e);

	public:
		~Engine() = default;
		Engine(Engine const&) = delete;
		void operator=(Engine const&) = delete;

		void Run();
		void PreUpdate(float deltaTime);
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void PostUpdate(float deltaTime);
		void Init();
		void Terminate();

		void OnEvent(Event& e);
		void PushSystem(System* system);

		inline Window& GetWindow() { return *_Window; }
		static Engine& Get() { static Engine instance; return instance; }

	private:
		bool _Running = true;

		ImGuiSystem* _ImGuiSystem = nullptr;
		CameraSystem* _CameraSystem = nullptr;

		Window* _Window;

		SystemCollection _SystemCollection;
	};
}

