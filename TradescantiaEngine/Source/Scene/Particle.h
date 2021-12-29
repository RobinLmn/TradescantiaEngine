#pragma once
#include <glm/glm.hpp>

namespace TradescantiaEngine
{
	struct Particle
	{
		glm::vec4 Position;
		glm::vec4 Color;
		glm::vec4 Force;
	};
}