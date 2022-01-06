#pragma once
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(int keycode) 
			: KeyCode(keycode) {}

		int KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatedCount) 
			: KeyEvent(keycode), RepeatedCount(repeatedCount) {}

		TSC_SET_EVENT_NAME("KeyPressed");

		int RepeatedCount;
	};

	class KeyReleasedEvent: public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		TSC_SET_EVENT_NAME("KeyReleased");
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		TSC_SET_EVENT_NAME("KeyTyped");
	};
}