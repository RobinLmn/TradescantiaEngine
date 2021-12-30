#include "tscpch.h"
#include "ImGuiSystem.h"

#include "Core/Engine.h"
#include "ImGuiBuild.h"
#include "imgui.h"

namespace TradescantiaEngine 
{
	void ImGuiSystem::Begin()
	{
		ZoneScoped
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiSystem::End()
	{
		ZoneScoped
		ImGuiIO& io = ImGui::GetIO();
		Engine& engine = Engine::Get();
		io.DisplaySize = ImVec2(static_cast<float>(engine.GetWindow().GetWidth()), static_cast<float>(engine.GetWindow().GetHeight()));
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ZoneScopedN("ImGuiSystem_UpdateViewports")
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiSystem::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  

		ImGui::StyleColorsDark();

		Engine& engine = Engine::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(engine.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiSystem::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiSystem::Update(float deltaTime)
	{
		ZoneScoped
		ImGui::Begin("Statistics");
		ImGui::Text("Frames: %d", static_cast<int>(1 / deltaTime));
		ImGui::End();
	}
}