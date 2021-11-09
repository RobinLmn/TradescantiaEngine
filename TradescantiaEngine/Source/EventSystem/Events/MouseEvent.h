#pragma once

#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: X(x), Y(y) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse;
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << X << ", " << Y;
			return ss.str();
		}

		SET_EVENTTYPE(EventType::MouseMoved);

		float X;
		float Y;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset)
			: XOffset(xOffset), YOffset(yOffset) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse;
		}

		SET_EVENTTYPE(EventType::MouseScrolled);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " <<XOffset << ", " << YOffset;
			return ss.str();
		}

		double XOffset;
		double YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			: Button(button) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton;
		}

		int Button;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		SET_EVENTTYPE(EventType::MouseButtonReleased);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << Button;
			return ss.str();
		}
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int repeatedCount)
			: MouseButtonEvent(button), RepeatedCount(repeatedCount) {}

		SET_EVENTTYPE(EventType::MouseButtonPressed);
		
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << Button;
			return ss.str();
		}

		int RepeatedCount;
	};
}