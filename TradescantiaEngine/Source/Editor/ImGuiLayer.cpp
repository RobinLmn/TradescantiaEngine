#include "tscpch.h"
#include "ImGuiLayer.h"

#include "GLFW/glfw3.h"
#include "Core/Core.h"
#include "Engine/Engine.h"
#include "Input/KeyCodes.h"

#include "Window/Platform/OpenGL/ImGuiOpenGlRenderer.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TradescantiaEngine 
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Engine& engine = Engine::Get();
		io.DisplaySize = ImVec2(engine.GetWindow().GetWidth(), engine.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(TSC_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsLight();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = TSC_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = TSC_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = TSC_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = TSC_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = TSC_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = TSC_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = TSC_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = TSC_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = TSC_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = TSC_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = TSC_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = TSC_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = TSC_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = TSC_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = TSC_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = TSC_KEY_A;
		io.KeyMap[ImGuiKey_C] = TSC_KEY_C;
		io.KeyMap[ImGuiKey_V] = TSC_KEY_V;
		io.KeyMap[ImGuiKey_X] = TSC_KEY_X;
		io.KeyMap[ImGuiKey_Y] = TSC_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = TSC_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.m_Button] = true;
		return false;
	}
	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.m_Button] = false;
		return false;
	}
	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.m_X, e.m_Y);
		return false;
	}
	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.m_XOffset;
		io.MouseWheel += e.m_YOffset;
		return false;
	}
	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.m_KeyCode] = true;

		io.KeyCtrl = io.KeysDown[TSC_KEY_LEFT_CONTROL] || io.KeysDown[TSC_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[TSC_KEY_LEFT_SHIFT] || io.KeysDown[TSC_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[TSC_KEY_LEFT_ALT] || io.KeysDown[TSC_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[TSC_KEY_LEFT_SUPER] || io.KeysDown[TSC_KEY_RIGHT_SUPER];
		return false;
	}
	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.m_KeyCode] = false;
		return false;
	}
	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.m_Width, e.m_Height);
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.m_Width, e.m_Height);
		return false;
	}
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.m_KeyCode;
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}
}