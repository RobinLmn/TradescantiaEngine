#pragma once
#include <glm/glm.hpp>

namespace  TradescantiaEngine
{
	class Camera
	{
	public:
		Camera(float l, float r, float t, float b);

		float GetRotation() const { return _Rotation; }
		void SetRotation(float rotation) { _Rotation = rotation; RecalculateViewMatrix(); }		
		
		glm::vec3 GetPosition() const { return _Position; }
		void SetPosition(glm::vec3 position) { _Position = position; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return _ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return _ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return _ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 _ProjectionMatrix;
		glm::mat4 _ViewMatrix;
		glm::mat4 _ViewProjectionMatrix;
		glm::vec3 _Position;
		float _Rotation = 0.0f;
	};
}