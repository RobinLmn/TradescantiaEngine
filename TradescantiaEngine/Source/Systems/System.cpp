#include "tscpch.h"
#include "System.h"

namespace TradescantiaEngine
{
	SystemStack::~SystemStack()
	{
		for (System* system : _Systems)
		{
			delete system;
		}
	}

	void SystemStack::PushSystem(System* system)
	{
		_Systems.emplace(_Systems.begin(), system);
	}

	void SystemStack::PopSystem(System* system)
	{
		auto iterator = std::find(_Systems.begin(), _Systems.end(), system);
		if (iterator != _Systems.end())
			_Systems.erase(iterator);
	}
}