#include "tscpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace TradescantiaEngine
{
	Camera::Camera(float fov, float width, float height, float nearPlane, float farPlane)
		: _ProjectionMatrix(glm::perspective(glm::radians(fov), (float)width / (float)height, nearPlane, farPlane))
	{
		_ViewMatrix = glm::lookAt(_Position, _Position + _Front, _Up);
		_ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(_CameraYaw)) * cos(glm::radians(_CameraPitch));
		front.y = sin(glm::radians(_CameraPitch));
		front.z = sin(glm::radians(_CameraYaw)) * cos(glm::radians(_CameraPitch));
		_Front = glm::normalize(front);

		_ViewMatrix = glm::lookAt(_Position, _Position + _Front, _Up);
		_ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
	}
}
