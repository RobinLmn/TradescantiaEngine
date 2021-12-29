#pragma once

#include "tscpch.h"
#include "Core/Core.h"

namespace TradescantiaEngine
{
#define TSC_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
#define TSC_SET_EVENT_NAME(name) static std::string GetStaticEventName() { return  name; } virtual std::string GetEventName() const override { return name; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual std::string GetEventName() const = 0;
		const bool isHandled() const { return _Handled; }

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
			if (_Event.GetEventName() == T::GetStaticEventName())
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
		return os << e.GetEventName();
	}
}