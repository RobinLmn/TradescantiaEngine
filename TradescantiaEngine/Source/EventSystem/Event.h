#pragma once

#include "tscpch.h"
#include "Core/Core.h"

namespace TradescantiaEngine
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow		 = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define SET_EVENTTYPE(type) static EventType GetStaticEventType() { return  type; } virtual EventType GetEventType() const override { return GetStaticEventType(); }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual std::string ToString() const = 0;
		virtual int GetCategoryFlags() const = 0;

		const bool isHandled() const { return _Handled; }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool _Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& e) : _Event(e) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (_Event.GetEventType() == T::GetStaticEventType())
			{
				_Event._Handled = func(*(T*)&_Event);
				return true;
			}
			return false;
		}

	private:
		 Event& _Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}