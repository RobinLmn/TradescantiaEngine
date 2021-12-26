#include "tscpch.h"
#include "ParticleSystem.h"
#include "Scene/Scene.h"
#include <glm/gtc/random.hpp>

namespace TradescantiaEngine
{
	void ParticleSystem::Init()
	{
		const int size = 100000;
		Particle* particles = new Particle[size];

		int min = -10;
		int max = 10;
		int dist = max - min;
		int r = 10;

		for (int i = 0; i < size; i++)
		{
			float x = glm::gaussRand(0.0f, 0.1f) * 12.0f;
			float y = glm::gaussRand(0.0f, 0.2f) * 0.2f;
			float z = glm::gaussRand(0.0f, 0.1f) * 12.0f;

			Particle particle;
			particle.Position = glm::vec3(x, y, z);
			float brightness = std::rand() / static_cast<float>(RAND_MAX);
			particle.Color = glm::vec3(brightness * 0.3f, 0.2f, 0.4f);
			particles[i] = particle;
		}

		Scene::SceneInstance->AddParticles(particles, size);
	}

	ParticleSystem::~ParticleSystem()
	{
	}

	void ParticleSystem::Update(float deltaTime)
	{
	}
}