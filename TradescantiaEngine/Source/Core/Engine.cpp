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
	bool Engine::OnWindowClose(WindowCloseEvent& e)
	{
		_Running = false;
		return true;
	}

	void Engine::OnEvent(Event& e)
	{
		EventDispatcher  dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(TSC_BIND_EVENT_FN(Engine::OnWindowClose));

		for (System* system : _SystemCollection)
		{
			system->OnEvent(e);
			if (e.isHandled())
				break;
		}
	}

	void Engine::PushSystem(System* system)
	{
		_SystemCollection.PushSystem(system);
	}

	void Engine::Init()
	{
		Log::Init();

		_Window = Window::Create(WindowProperties("TradescantiaEngine", /* width = */ 1080, /* height = */ 1080));
		_Window->SetEventCallback(TSC_BIND_EVENT_FN(Engine::OnEvent));

		PushSystem(_CameraSystem = new CameraSystem());
		PushSystem(_ImGuiSystem = new ImGuiSystem());
		PushSystem(new ParticleSystem);

		for (System* system : _SystemCollection)
			system->Init();

		Scene::Get().StartScene();
		TradescantiaEngine::RenderCommand::SetClearColor({ 0.f, 0.f, 0.f, 1.f });
	}

	void Engine::PreUpdate(float deltaTime)
	{
		ZoneScoped
		TradescantiaEngine::RenderCommand::Clear();

		TradescantiaEngine::Renderer::BeginScene(_CameraSystem->GetCamera());

		_ImGuiSystem->Begin();
	}

	void Engine::Update(float deltaTime)
	{
		ZoneScoped
		for (System* system : _SystemCollection)
			system->Update(deltaTime);
	}

	void Engine::FixedUpdate(float deltaTime)
	{
		ZoneScoped
		for (System* system : _SystemCollection)
			system->FixedUpdate(deltaTime);
	}

	void Engine::PostUpdate(float deltaTime)
	{
		ZoneScoped
		_ImGuiSystem->End();
		_Window->Update();
		TradescantiaEngine::Renderer::EndScene();
	}

	void Engine::Terminate()
	{
		for (System* system : _SystemCollection)
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
			FrameMark
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

			Scene::Get().Render();

			PostUpdate(deltaTime);
		}

		Terminate();
	}
}
