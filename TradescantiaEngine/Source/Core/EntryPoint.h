#pragma once

#ifdef TSC_PLATFORM_WINDOWS

#include "EventSystem/Event.h"

TradescantiaEngine::Engine* TradescantiaEngine::CreateEngine();

int main(int argc, char** argv)
{
	TradescantiaEngine::Log::Init();
	auto g_Engine = TradescantiaEngine::CreateEngine();
	g_Engine->Run();
	delete g_Engine;
}

#endif