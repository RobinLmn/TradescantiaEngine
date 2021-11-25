#include "tscpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Core/Engine.h"

namespace TradescantiaEngine
{

	Input* Input::_Instance = new WindowsInput();

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
	glm::vec2 WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}
}