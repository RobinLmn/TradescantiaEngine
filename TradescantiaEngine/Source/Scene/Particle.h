#pragma once
#include <glm/glm.hpp>

namespace TradescantiaEngine
{
	struct Particle
	{
		alignas(16) glm::vec3 Position;
		alignas(16) glm::vec3 Color;
		alignas(16) glm::vec3 Force;
		alignas(16) glm::vec3 Velocity;
	};
}