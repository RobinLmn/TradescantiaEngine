#include "tscpch.h"
#include "ParticleSystem.h"
#include "Scene/Scene.h"
#include <glm/gtc/random.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace TradescantiaEngine
{
	void ParticleSystem::Init()
	{
		const int size = 5000;

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
		ZoneScoped
		std::vector<Particle>& scene_particles = Scene::Get().GetParticles();

		auto update_particle_set_forces = [](std::vector<Particle>* particles, size_t start_index, size_t end_index)
		{
			ZoneScoped
			for (int i = start_index; i < end_index; i++)
			{
				Particle& particle = particles->at(i);

				for (int j = i; j < particles->size(); j++)
				{
					const glm::vec3 PosA = particle.Position;
					const glm::vec3 PosB = particles->at(j).Position;

					const float Dist = glm::abs(glm::distance(PosA, PosB));

					if (Dist != 0)
					{
					const glm::vec3 UnitVec = (PosB - PosA) / Dist;
					const glm::vec3 GravForce = UnitVec * particles[j].Mass * particle.Mass / (Dist * Dist + 0.015f);

						particle.Force += GravForce;
						particles->at(j).Force -= GravForce;
					}
				}
			}
		};

		{
			ZoneScopedN("ComputeForces")

			std::vector<std::thread> threads;
			const size_t num_workers = std::thread::hardware_concurrency();
			
			const size_t particles_per_thread = scene_particles.size() / num_workers;
			for (size_t i = 0; i < num_workers - 1; ++i)
			{
				threads.emplace_back(update_particle_set_forces, &scene_particles, i * particles_per_thread, (i+1)*particles_per_thread);
			}
			threads.emplace_back(update_particle_set_forces, &scene_particles, (num_workers - 1) * particles_per_thread, scene_particles.size());

			for (std::thread& thread : threads)
			{
				thread.join();
			}
		}

		{
			ZoneScopedN("ApplyForces")
			for (int i = 0; i < scene_particles.size(); i++)
			{
				scene_particles[i].Velocity += scene_particles[i].Force / scene_particles[i].Mass * deltaTime;
				scene_particles[i].Position += scene_particles[i].Velocity * deltaTime;
				scene_particles[i].Force = glm::vec3(0.f);
			}
		}
	}
}