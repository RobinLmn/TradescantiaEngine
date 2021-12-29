#pragma once
#include <glm/glm.hpp>

namespace  TradescantiaEngine
{
	class Camera
	{
	public:
		Camera(float fov, float width, float height, float nearPlane, float farPlane);

		float GetYaw() const { return _CameraYaw; }
		void IncYaw(float yaw) { _CameraYaw += yaw; RecalculateViewMatrix(); }

		float GetPitch() const { return _CameraPitch; }
		void IncPitch(float pitch) { _CameraPitch += pitch; RecalculateViewMatrix(); }
		
		glm::vec3 GetPosition() const { return _Position; }
		void SetPosition(glm::vec3 position) { _Position = position; RecalculateViewMatrix(); }

		glm::vec3 GetUp() const { return _Up; }
		glm::vec3 GetFront() const { return _Front; }

		const glm::mat4& GetProjectionMatrix() const { return _ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return _ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return _ViewProjectionMatrix; }

		float Speed = 0.5f;
		float Sensitivity = 0.1f;


	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 _ProjectionMatrix;
		glm::mat4 _ViewMatrix;
		glm::mat4 _ViewProjectionMatrix;

		glm::vec3 _Position = glm::vec3(0.0,0.0,10.0f);
		glm::vec3 _Up = glm::vec3(0.0, 1.0, .0f);
		glm::vec3 _Front = glm::vec3(0.0, 0.0, -1.0f);

		float _CameraYaw = -90.0f;
		float _CameraPitch = -23.f;
	};
}