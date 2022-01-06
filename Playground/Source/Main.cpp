#include <TradescantiaEngine.h>

#ifdef TSC_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	TradescantiaEngine::Engine& engine = TradescantiaEngine::Engine::Get();
	engine.Run();
}

#endif