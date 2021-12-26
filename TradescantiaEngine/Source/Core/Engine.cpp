#include "tscpch.h"

#include "Engine.h"
#include "Input.h"
#include "Log.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"

#include "Scene/Scene.h"

#include "Systems/ParticleSystem.h"

#define FIXED_UPDATE_TIME 0.20f

namespace TradescantiaEngine 
{
	Engine* Engine::_Instance = nullptr;
	
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Engine::Engine() 
	{
		TSC_ASSERT(!_Instance, "Engine instance was already created");
		_Instance = this;
		_Window = Window::Create(WindowProperties("TradescantiaEngine", /* width = */ 1080, /* height = */ 1080));
		_Window->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));

		PushSystem(_CameraSystem = new CameraSystem());
		PushSystem(_ImGuiSystem = new ImGuiSystem());
		PushSystem(new ParticleSystem);
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

		Scene::SceneInstance->StartScene();
	}

	void Engine::PreUpdate(float deltaTime)
	{
		TradescantiaEngine::RenderCommand::SetClearColor({ 0.f, 0.f, 0.f, 1.f });
		TradescantiaEngine::RenderCommand::Clear();

		TradescantiaEngine::Renderer::BeginScene(_CameraSystem->GetCamera());

		_ImGuiSystem->Begin();
	}

	void Engine::Update(float deltaTime)
	{
		for (System* system : _SystemStack)
			system->Update(deltaTime);
	}

	void Engine::FixedUpdate(float deltaTime)
	{
		for (System* system : _SystemStack)
			system->FixedUpdate(deltaTime);
	}

	void Engine::PostUpdate(float deltaTime)
	{
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
		
		std::chrono::high_resolution_clock clock;

		using seconds = std::chrono::duration<float, std::ratio<1>>;
		auto lastTime = clock.now();
		float lag = 0.0;

		while (_Running)
		{
			const float deltaTime = std::chrono::duration_cast<seconds>(clock.now() - lastTime).count();
			lastTime = clock.now();
			lag += deltaTime;

			PreUpdate(deltaTime);

			while (lag >= FIXED_UPDATE_TIME)
			{
				lag -= FIXED_UPDATE_TIME;
				FixedUpdate(FIXED_UPDATE_TIME);
			}

			Update(deltaTime);

			Scene::SceneInstance->Render();

			PostUpdate(deltaTime);
		}

		Terminate();
	}
}
