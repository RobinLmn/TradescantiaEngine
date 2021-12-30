#include "tscpch.h"
#include "ParticleSystem.h"
#include "Scene/Scene.h"
#include <glm/gtc/random.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace TradescantiaEngine
{
	void ParticleSystem::Init()
	{
		const int size = 1200;

		Scene& scene = Scene::Get();
		scene.Reserve(size + 1);

		for (int i = 0; i < size; i++)
		{
			glm::vec3 position;
			
			do {
				position = glm::ballRand(50.f);
				position.y *= 0.01f;
			} while (glm::length(position) < 2.0f);

			const float brightness = glm::linearRand(0.f, 1.f);
			const float dist = glm::length(position) / 50.f;

			Particle particle;
			particle.Position = position;
			particle.Mass = 1.f;
			particle.Color = glm::vec3(1.f - dist, 0.4f, dist);
			particle.Velocity = glm::normalize(glm::cross(position, glm::vec3(0.f, 1.f, 0.f)));
			particle.Force = glm::vec3(0.f);

			scene.AddParticle(particle);
		}

		Particle sbmh;
		sbmh.Position = glm::vec3(0.f);
		sbmh.Mass = 10.f;
		sbmh.Color = glm::vec3(0.f, 0.f, 0.f);
		sbmh.Velocity = glm::vec3(0.f);
		sbmh.Force = glm::vec3(0.f);
		scene.AddParticle(sbmh);
	}

	void ParticleSystem::FixedUpdate(float deltaTime)
	{
		std::vector<Particle>& particles = Scene::Get().GetParticles();

		for (int i = 0; i < particles.size() - 1; i++)
		{
			Particle& particle = particles[i];

			for (int j = i+1; j < particles.size(); j++)
			{
				const glm::vec3 PosA = particle.Position;
				const glm::vec3 PosB = particles[j].Position;

				const float Dist = std::abs(glm::distance(PosA, PosB));

				if (Dist != 0)
				{
					const glm::vec3 UnitVec = (PosB - PosA) / Dist;
					const glm::vec3 GravForce = UnitVec * particles[j].Mass * particle.Mass / (Dist * Dist + 0.015f);

					particle.Force += GravForce;
					particles[j].Force -= GravForce;
				}
			}
		}

		for (int i = 0; i < particles.size(); i++)
		{
			particles[i].Velocity += particles[i].Force / particles[i].Mass * deltaTime;
			particles[i].Position += particles[i].Velocity * deltaTime;
			particles[i].Force = glm::vec3(0.f);
		}
	}
}