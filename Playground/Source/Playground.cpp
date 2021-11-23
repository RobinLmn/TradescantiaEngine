#include <TradescantiaEngine.h>
#include "ParticleSystem.h"

class Playground : public TradescantiaEngine::Engine
{
public:
	Playground()
	{
		PushLayer(new ParticleSystem);
	};

	~Playground() {};
};

TradescantiaEngine::Engine* TradescantiaEngine::CreateEngine()
{
	return new Playground();
}
