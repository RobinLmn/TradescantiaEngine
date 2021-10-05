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
			return std::string("KeyPressed key=%d ; count=%d", m_KeyCode, m_RepeatedCount);
		}

		SET_EVENTTYPE(EventType::KeyPressed);

		int m_RepeatedCount;
	};

	class TSC_API KeyReleasedEvent: public KeyEvent
	{
		virtual std::string ToString() const override
		{
			return std::string("KeyReleased key=%d", m_KeyCode);
		}

		SET_EVENTTYPE(EventType::KeyReleased);
	};
}