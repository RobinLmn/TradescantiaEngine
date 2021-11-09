#pragma once

#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	class WindowCloseEvent : public Event
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

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: Width(width), Height(height) {}

		SET_EVENTTYPE(EventType::WindowResize);
		virtual int GetCategoryFlags() const override { return EventCategoryWindow; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize (" << Width << ";" << Height << ")";
			return ss.str();
		}

		unsigned int Width;
		unsigned int Height;
	};
}