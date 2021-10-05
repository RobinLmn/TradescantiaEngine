#pragma once
#include "Core/Core.h"

namespace TradescantiaEngine {
	class TSC_API Engine
	{
	public:
		Engine();
		~Engine();

		void Run();
	};

	Engine* CreateEngine();
}

