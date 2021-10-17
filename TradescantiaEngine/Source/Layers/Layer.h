#pragma once

#include "Core/Core.h"
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class TSC_API Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		std::string debugName;
	};
}