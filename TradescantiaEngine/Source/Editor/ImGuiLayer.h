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

		void OnUpdate() override;
		void OnEvent(Event& e) override;

		void OnAttach() override;
		void OnDetach() override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		float m_Time;
	};
};

