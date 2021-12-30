#include "tscpch.h"
#include "ParticleSystem.h"
#include "Scene/Scene.h"
#include <glm/gtc/random.hpp>

namespace TradescantiaEngine
{
	void ParticleSystem::Init()
	{
		const int size = 400;

		Scene& scene = Scene::Get();
		scene.Reserve(size);

		const int min = -10;
		const int max = 10;
		const int dist = max - min;
		const int r = 10;

		for (int i = 0; i < size; i++)
		{
			const float x = glm::gaussRand(0.0f, 0.1f) * 12.0f;
			const float y = glm::gaussRand(0.0f, 0.2f) * 0.2f;
			const float z = glm::gaussRand(0.0f, 0.1f) * 12.0f;

			Particle particle;
			particle.Position = glm::vec4(x, y, z, 0);
			const float brightness = std::rand() / static_cast<float>(RAND_MAX);
			particle.Color = glm::vec4(brightness * 0.3f, 0.2f, 0.4f, 1.f);
			scene.AddParticle(particle);
		}
	}

	void ParticleSystem::FixedUpdate(float deltaTime)
	{
		std::vector<Particle>& particles = Scene::Get().GetParticles();

		for (int i = 0; i < particles.size(); i++)
		{
			Particle& particle = particles[i];

			for (int j = i; j < particles.size(); j++)
			{
				const glm::vec3 PosA = particle.Position;
				const glm::vec3 PosB = particles[j].Position;

				const float Dist = std::abs(glm::distance(PosA, PosB));

				if (Dist != 0)
				{
					const glm::vec3 UnitVec = (PosB - PosA) / Dist;
					const glm::vec3 GravForce = UnitVec / (Dist * Dist);

					particle.Force += GravForce;
					particles[j].Force -= GravForce;
				}
			}

			particle.Position += particle.Force * deltaTime * deltaTime;
			particle.Force = glm::vec3(0.f, 0.f, 0.f);
		}
	}
}