#pragma once

#include "Window/Window.h"
#include <GLFW/glfw3.h>

namespace TradescantiaEngine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
	
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool isEnabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData
		{
			unsigned int Width, Height;
			std::string Title;
			bool VSync;
			
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}

