#pragma once

#include "Core.h"

namespace TradescantiaEngine
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return _Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return _Instance->IsMouseButtonPressedImpl(button); }
		inline static std::tuple<double, double> GetMousePos() { return _Instance->GetMousePosImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::tuple<double, double> GetMousePosImpl() = 0;
	private:
		static Input* _Instance;
	};
}