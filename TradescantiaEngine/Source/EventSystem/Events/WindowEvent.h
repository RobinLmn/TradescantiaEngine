#pragma once

#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class TSC_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		SET_EVENTTYPE(EventType::WindowClose);
		virtual int GetCategoryFlags() const override { return EventCategoryWindow; }
	
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseCloseEvent";
			return ss.str();;
		}
	};

	class TSC_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(float width, float height)
			: Width(width), Height(height) {}

		SET_EVENTTYPE(EventType::WindowResize);
		virtual int GetCategoryFlags() const override { return EventCategoryWindow; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize (" << Width << ";" << Height << ")";
			return ss.str();
		}

		float Width;
		float Height;
	};
}