#pragma once

#ifdef TSC_PLATFORM_WINDOWS

#include "EventSystem/Event.h"

TradescantiaEngine::Engine* TradescantiaEngine::CreateEngine();

int main(int argc, char** argv)
{
	TradescantiaEngine::Log::Init();
	auto engine = TradescantiaEngine::CreateEngine();
	engine->Run();
	delete engine;
}

#endif