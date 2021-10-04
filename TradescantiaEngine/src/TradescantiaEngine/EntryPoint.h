#pragma once

#ifdef TSC_PLATFORM_WINDOWS

TradescantiaEngine::Application* TradescantiaEngine::CreateApplication();

int main(int argc, char** argv)
{
	TradescantiaEngine::Log::Init();
	auto app = TradescantiaEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif