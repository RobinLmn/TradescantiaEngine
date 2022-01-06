#include "tscpch.h"
#include "System.h"

namespace TradescantiaEngine
{
	SystemCollection::~SystemCollection()
	{
		for (System* system : _Systems)
			delete system;
	}

	void SystemCollection::PushSystem(System* system)
	{
		_Systems.emplace(_Systems.begin(), system);
	}

	void SystemCollection::PopSystem(System* system)
	{
		auto iterator = std::find(_Systems.begin(), _Systems.end(), system);
		if (iterator != _Systems.end())
			_Systems.erase(iterator);
	}
}