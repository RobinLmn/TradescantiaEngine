#pragma once

#include "Window/Window.h"
#include "Renderer/OpenGLContext.h"
#include <GLFW/glfw3.h>

namespace TradescantiaEngine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
	
		inline unsigned int GetWidth() const override { return _Data.Width; }
		inline unsigned int GetHeight() const override { return _Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { _Data.EventCallback = callback; }
		void SetVSync(bool isEnabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return _Window; }

	private:
		virtual void Init(const WindowProperties& props);
		virtual void Shutdown();

		GLFWwindow* _Window;
		OpenGLContext* _Context;

		struct WindowData
		{
			bool VSync = false;
			unsigned int Width = 0;
			unsigned int Height = 0;
			std::string Title;
			EventCallbackFn EventCallback;
		};

		WindowData _Data;
	};
}

