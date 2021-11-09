#pragma once
#include "Core/Core.h"
#include "Core/Input.h"

namespace TradescantiaEngine
{
	class TSC_API WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::tuple<float, float> GetMousePosImpl() override;
	};
}