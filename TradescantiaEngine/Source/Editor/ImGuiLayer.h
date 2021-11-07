#pragma once

#include "Layers/Layer.h"

namespace TradescantiaEngine
{
	class TSC_API ImGuiLayer : public Layer
	{
	public: 
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate() override;
		void OnEvent(Event& e) override;

		void OnAttach() override;
		void OnDetach() override;
	private:
		float m_Time;
	};
};

