#pragma once

#include "Layers/Layer.h"

#include "EventSystem/Events/WindowEvent.h"
#include "EventSystem/Events/KeyEvent.h"
#include "EventSystem/Events/MouseEvent.h"

namespace TradescantiaEngine
{
	class TSC_API ImGuiLayer : public Layer
	{
	public: 
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	};
};

