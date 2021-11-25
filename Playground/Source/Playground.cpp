#include <TradescantiaEngine.h>

class Playground : public TradescantiaEngine::Engine
{
public:
	Playground()
	{
	};

	~Playground() {};
};

TradescantiaEngine::Engine* TradescantiaEngine::CreateEngine()
{
	return new Playground();
}
