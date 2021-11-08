#pragma once

#include "Core/Core.h"

namespace TradescantiaEngine
{
	class TSC_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::tuple<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::tuple<float, float> GetMousePosImpl() = 0;
	private:
		static Input* s_Instance;
	};
}