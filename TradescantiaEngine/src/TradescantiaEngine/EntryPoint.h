#pragma once

#ifdef TSC_PLATFORM_WINDOWS

TradescantiaEngine::Application* TradescantiaEngine::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Welcome to Tradescantia Engine!" << std::endl;
	auto app = TradescantiaEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif