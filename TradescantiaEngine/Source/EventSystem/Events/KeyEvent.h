#pragma once
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class KeyEvent : public Event
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

	class KeyPressedEvent : public KeyEvent
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

		TSC_SET_EVENT_TYPE(EventType::KeyPressed);

		int RepeatedCount;
	};

	class KeyReleasedEvent: public KeyEvent
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

		TSC_SET_EVENT_TYPE(EventType::KeyReleased);
	};

	class KeyTypedEvent : public KeyEvent
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

		TSC_SET_EVENT_TYPE(EventType::KeyTyped);
	};
}