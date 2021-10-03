#pragma once
#include "Core.h"

namespace TradescantiaEngine {
	class TSC_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	Application* CreateApplication();
}

