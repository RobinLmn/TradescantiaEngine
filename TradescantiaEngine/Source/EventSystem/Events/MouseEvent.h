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
			return std::string("MouseMoved to (%f, %f)", m_X, m_Y);
		}

		SET_EVENTTYPE(EventType::MouseMoved);

		float m_X;
		float m_Y;
	};

	class TSC_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryMouse;
		}

		SET_EVENTTYPE(EventType::MouseScrolled);

		virtual std::string ToString() const override
		{
			return std::string("MouseScrolled by (%f, %f)", m_XOffset, m_YOffset);
		}

		float m_XOffset;
		float m_YOffset;
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

		SET_EVENTTYPE(EventType::MouseButtonReleased);

		virtual std::string ToString() const override
		{
			return std::string("MouseButtonReleased key=%", m_Button);
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
			return std::string("MouseButtonPressed key=% ; count=%f", m_Button, m_RepeatedCount);
		}

		int m_RepeatedCount;
	};
}