#include "tscpch.h"
#include "ParticleSystem.h"
#include "Scene/Scene.h"
#include <glm/gtc/random.hpp>

namespace TradescantiaEngine
{
	void ParticleSystem::Init()
	{
		const int size = 300;

		Scene& scene = Scene::Get();
		scene.Reserve(size);

		const int min = -10;
		const int max = 10;
		const int dist = max - min;
		const int r = 10;

		for (int i = 0; i < size; i++)
		{
			glm::vec3 position = glm::ballRand(25.f);
			position.y *= 0.1f;
			const float brightness = std::rand() / static_cast<float>(RAND_MAX);
			const float dist = glm::length(position) / 20.f;

			Particle particle;
			particle.Position = glm::vec4(position, 0);
			particle.Color = glm::vec3(1.f - dist, 0.4f, dist);
			particle.Velocity = glm::vec3(0.f);
			particle.Force = glm::vec3(0.f);

			scene.AddParticle(particle);
		}
	}

	void ParticleSystem::FixedUpdate(float deltaTime)
	{
		std::vector<Particle>& particles = Scene::Get().GetParticles();

		for (int i = 0; i < particles.size() - 1; i++)
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
					const glm::vec3 GravForce = UnitVec / (Dist * Dist + 100.f);

					particle.Force += GravForce;
					particles[j].Force -= GravForce;
				}
			}
		}

		for (int i = 0; i < particles.size(); i++)
		{
			particles[i].Velocity += particles[i].Force * deltaTime;
			particles[i].Position += particles[i].Velocity * deltaTime;
			particles[i].Force = glm::vec3(0.f);
		}
	}
}