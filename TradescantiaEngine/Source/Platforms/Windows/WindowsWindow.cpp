#include "tscpch.h"
#include "WindowsWindow.h"

#include "EventSystem/Events/KeyEvent.h"
#include "EventSystem/Events/MouseEvent.h"
#include "EventSystem/Events/WindowEvent.h"

#include <glad/glad.h>

namespace TradescantiaEngine
{
	static bool _GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		TSC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		_Data.Title = props.Title;
		_Data.Height = props.Height;
		_Data.Width = props.Width;

		TSC_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!_GLFWInitialized)
		{
			int success = glfwInit();
			TSC_CORE_ASSERT(success, "Could not initialize GLFW");
			_GLFWInitialized = true;
		}

		_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), _Data.Title.c_str(), /*monitor = */ nullptr, /*window = */ nullptr);
		_Context = new OpenGLContext(_Window);
		_Context->Init();

		glfwSetWindowUserPointer(_Window, &_Data);
		SetVSync(true);

		// Set glfw callbacks

		glfwSetCharCallback(_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetWindowSizeCallback(_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			
			data.Width = static_cast<unsigned int>(width);
			data.Height = static_cast<unsigned int>(height);

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(_Window, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					MouseButtonPressedEvent event(button, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event(xOffset, yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(_Window);
	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool isEnabled)
	{
		glfwSwapInterval(isEnabled);
		_Data.VSync = isEnabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return _Data.VSync;
	}
}