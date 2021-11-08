#include "tscpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Engine/Engine.h"

namespace TradescantiaEngine
{

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::tuple<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::tuple<float, float>(xpos, ypos);
	}
}