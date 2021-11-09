#pragma once
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class TSC_API KeyEvent : public Event
	{
	public:
		KeyEvent(int keycode) 
			: KeyCode(keycode) {}

		virtual int GetCategoryFlags() const override
		{
			return EventCategoryInput | EventCategoryKeyboard;
		}

		int KeyCode;
	};

	class TSC_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatedCount) 
			: KeyEvent(keycode), RepeatedCount(repeatedCount) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << KeyCode << " (" << RepeatedCount << " repeats)";
			return ss.str();
		}

		SET_EVENTTYPE(EventType::KeyPressed);

		int RepeatedCount;
	};

	class TSC_API KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << KeyCode;
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
			ss << "KeyTypedEvent: " << KeyCode;
			return ss.str();
		}

		SET_EVENTTYPE(EventType::KeyTyped);
	};
}