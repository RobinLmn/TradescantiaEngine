#pragma once
#include <TradescantiaEngine.h>

using namespace TradescantiaEngine;

class PlaygroundLayer : public Layer
{
public:
	PlaygroundLayer()
		: Layer("PlaygroundLayer")
	{
	}

	void OnUpdate() override
	{
	}

	void OnEvent(Event& event) override
	{
		TSC_TRACE("{0}", event);
	}
};

class Playground : public TradescantiaEngine::Engine 
{
public:
	Playground() 
	{
		PushLayer(new PlaygroundLayer());
		PushOverlay(new ImGuiLayer());
	};

	~Playground() {};
};