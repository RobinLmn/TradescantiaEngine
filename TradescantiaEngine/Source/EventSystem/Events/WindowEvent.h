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
			return std::string("WindowClose");
		}
	};

	class TSC_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(float width, float height)
			: m_Width(width), m_Height(height) {}

		SET_EVENTTYPE(EventType::WindowResize);
		virtual int GetCategoryFlags() const override { return EventCategoryWindow; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize (" << m_Width << ";" << m_Height << ")";
			return ss.str();
		}

		float m_Width;
		float m_Height;
	};
}