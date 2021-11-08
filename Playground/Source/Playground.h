#pragma once
#include <TradescantiaEngine.h>

using namespace TradescantiaEngine;

class Playground : public TradescantiaEngine::Engine 
{
public:
	Playground() 
	{
		PushOverlay(new ImGuiLayer());
	};

	~Playground() {};
};