#pragma once

#include "Core/System.h"

#include "EventSystem/Events/WindowEvent.h"
#include "EventSystem/Events/KeyEvent.h"
#include "EventSystem/Events/MouseEvent.h"

namespace TradescantiaEngine
{
	class ImGuiSystem : public System
	{
	public: 
		ImGuiSystem() = default;
		~ImGuiSystem() = default;

		void Init() override;
		void Terminate() override;
		void Update(float deltaTime) override;

		void Begin();
		void End();
	};
};

