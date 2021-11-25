#pragma once

#include "tscpch.h"
#include "Core/Core.h"
#include "EventSystem/Event.h"

namespace TradescantiaEngine
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title, unsigned int width, unsigned int height)
			: Height(height), Width(width), Title(title)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual void Update() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetVSync(bool isEnabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& props);
	};
}