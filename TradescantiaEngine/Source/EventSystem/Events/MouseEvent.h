#pragma once

#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class TSC_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_X(x), m_Y(y) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse;
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_X << ", " << m_Y;
			return ss.str();
		}

		SET_EVENTTYPE(EventType::MouseMoved);

		float m_X;
		float m_Y;
	};

	class TSC_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse;
		}

		SET_EVENTTYPE(EventType::MouseScrolled);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		double m_XOffset;
		double m_YOffset;
	};

	class TSC_API MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton;
		}

		int m_Button;
	};

	class TSC_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		SET_EVENTTYPE(EventType::MouseButtonReleased);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
	};

	class TSC_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button, int repeatedCount)
			: MouseButtonEvent(button), m_RepeatedCount(repeatedCount) {}

		SET_EVENTTYPE(EventType::MouseButtonPressed);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		int m_RepeatedCount;
	};
}