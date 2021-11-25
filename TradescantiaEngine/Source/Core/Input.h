#pragma once

#include "Core.h"
#include <glm/glm.hpp>

namespace TradescantiaEngine
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return _Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return _Instance->IsMouseButtonPressedImpl(button); }
		inline static glm::vec2 GetMousePos() { return _Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual glm::vec2 GetMousePosImpl() = 0;
	private:
		static Input* _Instance;
	};
}