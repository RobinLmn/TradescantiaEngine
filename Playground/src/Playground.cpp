#include <TradescantiaEngine.h>
#include "Playground.h"


TradescantiaEngine::Application* TradescantiaEngine::CreateApplication()
{
	return new Playground();
}
