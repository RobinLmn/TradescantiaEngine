#pragma once

#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		TSC_SET_EVENT_NAME("WindowCloseEvent");
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: Width(width), Height(height) {}

		TSC_SET_EVENT_NAME("WindowResize");

		unsigned int Width;
		unsigned int Height;
	};
}