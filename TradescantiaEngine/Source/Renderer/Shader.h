#pragma once

#include <string>
#include <glm/glm.hpp>

namespace TradescantiaEngine
{
	class Shader
	{
	public:
		virtual void Use() = 0;
		virtual void SetBool(const std::string& name, bool value) const = 0;
		virtual void SetInt(const std::string& name, int value) const = 0;
		virtual void SetFloat(const std::string& name, float value) const = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) const = 0;

		static Shader* Create(const char* vertexPath, const char* fragmentPath);

		unsigned int ID;
	};
}