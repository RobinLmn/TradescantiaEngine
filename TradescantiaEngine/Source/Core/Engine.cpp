#include "tscpch.h"

#include "Engine.h"
#include "Input.h"
#include "Log.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

namespace TradescantiaEngine 
{
	Engine* Engine::_Instance = nullptr;
	
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Engine::Engine() 
	{
		TSC_ASSERT(!_Instance, "Engine instance was already created");
		_Instance = this;
		_Window = Window::Create(WindowProperties("TradescantiaEngine", /* width = */ 720, /* height = */ 720));
		_Window->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));

		_ImGuiSystem = new ImGuiSystem();
		_CameraSystem = new CameraSystem();

		PushSystem(_CameraSystem);
		PushSystem(_ImGuiSystem);
	}

	Engine::~Engine()
	{
	}

	bool Engine::OnWindowClose(WindowCloseEvent& e)
	{
		_Running = false;
		return true;
	}

	void Engine::OnEvent(Event& e)
	{
		EventDispatcher  dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Engine::OnWindowClose));

		for (auto iterator = _SystemStack.end(); iterator != _SystemStack.begin();)
		{
			(*--iterator)->OnEvent(e);
			if (e.isHandled())
				break;
		}
	}

	void Engine::PushSystem(System* system)
	{
		_SystemStack.PushSystem(system);
	}

	void Engine::Init()
	{
		for (System* system : _SystemStack)
			system->Init();
	}

	void Engine::Update(float deltaTime)
	{
		TradescantiaEngine::RenderCommand::SetClearColor({ 1.f, 1.f, 1.f, 1.f });
		TradescantiaEngine::RenderCommand::Clear();

		TradescantiaEngine::Renderer::BeginScene(_CameraSystem->GetCamera());

		_ImGuiSystem->Begin();

		for (System* system : _SystemStack)
			system->Update(deltaTime);

		_ImGuiSystem->End();

		_Window->Update();

		TradescantiaEngine::Renderer::EndScene();
	}

	void Engine::Terminate()
	{
		for (System* system : _SystemStack)
			system->Terminate();
	}

	void Engine::Run()
	{
		Init();
		while (_Running)
		{
			Update(1.0f);
		}
		Terminate();
	}
}
