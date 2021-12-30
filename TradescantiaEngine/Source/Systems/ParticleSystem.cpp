#include "tscpch.h"
#include "ParticleSystem.h"
#include "Scene/Scene.h"
#include <glm/gtc/random.hpp>

namespace TradescantiaEngine
{
	void ParticleSystem::Init()
	{
		const int size = 5000;

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
						const glm::vec3 UnitVec = glm::normalize(PosB - PosA);
						const glm::vec3 GravForce = UnitVec / (Dist * Dist + 100.f);

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
				scene_particles[i].Velocity += scene_particles[i].Force * deltaTime;
				scene_particles[i].Position += scene_particles[i].Velocity * deltaTime;
				scene_particles[i].Force = glm::vec3(0.f);
			}
		}
	}
}