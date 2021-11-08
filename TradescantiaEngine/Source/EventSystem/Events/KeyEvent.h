#pragma once
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class TSC_API KeyEvent : public Event
	{
	public:
		KeyEvent(int keycode) 
			: m_KeyCode(keycode) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryKeyboard;
		}

		int m_KeyCode;
	};

	class TSC_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatedCount) 
			: KeyEvent(keycode), m_RepeatedCount(repeatedCount) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatedCount << " repeats)";
			return ss.str();
		}

		SET_EVENTTYPE(EventType::KeyPressed);

		int m_RepeatedCount;
	};

	class TSC_API KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		SET_EVENTTYPE(EventType::KeyReleased);
	};

	class TSC_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		SET_EVENTTYPE(EventType::KeyTyped);
	};
}