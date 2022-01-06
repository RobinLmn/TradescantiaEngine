#pragma once

#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: X(x), Y(y) {}

		TSC_SET_EVENT_NAME("MouseMoved");

		float X;
		float Y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset)
			: XOffset(xOffset), YOffset(yOffset) {}

		TSC_SET_EVENT_NAME("MouseScrolled");

		double XOffset;
		double YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			: Button(button) {}

		int Button;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		TSC_SET_EVENT_NAME("MouseButtonReleased");
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int repeatedCount)
			: MouseButtonEvent(button), RepeatedCount(repeatedCount) {}

		TSC_SET_EVENT_NAME("MouseButtonPressed");

		int RepeatedCount;
	};
}