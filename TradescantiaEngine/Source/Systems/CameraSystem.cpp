#include "tscpch.h"
#include "CameraSystem.h"
#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace TradescantiaEngine
{
	CameraSystem::CameraSystem()
		: _MousePosition(TradescantiaEngine::Input::GetMousePos()),
		  _CameraPosition(glm::vec3(0.f, 0.f, 40.f)),
		  _Camera(45.0f, 1, 1, 0.1f, 100.0f)
	{
	}

	void CameraSystem::Update(float deltaTime)
	{
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_A))
			_CameraPosition -= glm::normalize(glm::cross(_Camera.GetFront(), _Camera.GetUp())) * _Camera.Speed;
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_D))
			_CameraPosition += glm::normalize(glm::cross(_Camera.GetFront(), _Camera.GetUp())) * _Camera.Speed;
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_S))
			_CameraPosition -= _Camera.Speed * _Camera.GetFront();
		if (TradescantiaEngine::Input::IsKeyPressed(TSC_KEY_W))
			_CameraPosition += _Camera.Speed * _Camera.GetFront();

		if (TradescantiaEngine::Input::IsMouseButtonPressed(TSC_MOUSE_BUTTON_2))
		{
			_Camera.IncYaw((TradescantiaEngine::Input::GetMousePos().x - _MousePosition.x) * _Camera.Sensitivity);
			_Camera.IncPitch((_MousePosition.y - TradescantiaEngine::Input::GetMousePos().y) * 0.1f);
		}

		_MousePosition = TradescantiaEngine::Input::GetMousePos();

		_Camera.SetPosition(_CameraPosition);
	}
}