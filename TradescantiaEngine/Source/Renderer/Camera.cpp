#include "tscpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace TradescantiaEngine
{
	Camera::Camera(float l, float r, float t, float b)
		: _ProjectionMatrix(glm::ortho(l, r, b, t, -20.f, 20.f)), _ViewMatrix(1.0f)
	{
		_ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), _Position) * glm::rotate(glm::mat4(1.0f), _Rotation, glm::vec3(0, 0, 1));
		_ViewMatrix = glm::inverse(transform);
		_ViewProjectionMatrix = _ProjectionMatrix * _ViewMatrix;
	}
}
