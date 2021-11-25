#pragma once
#include "System.h"
#include <glm/glm.hpp>
#include "Renderer/Camera.h"

namespace TradescantiaEngine
{
	class CameraSystem : public System
	{
	public:
		CameraSystem();
		virtual ~CameraSystem() = default;

		virtual void Update(float deltaTime) override;

		Camera& GetCamera() { return _Camera; }

	private:
		Camera _Camera;
		glm::vec3 _CameraPosition;
		glm::vec2 _MousePosition;
	};
}

