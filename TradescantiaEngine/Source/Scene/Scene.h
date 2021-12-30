#pragma once
#include "Particle.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace TradescantiaEngine
{
	class Scene
	{
	private:
		Scene() = default;

	public:
		~Scene() = default;
		Scene(Scene const&) = delete;
		Scene operator=(Scene const&) = delete;

		void StartScene();

		void Reserve(int size) { _Particles.reserve(size); }
		void AddParticle(Particle& particle);
		size_t GetCount() const { return _Particles.size(); }
		std::vector<Particle>& GetParticles() { return _Particles; }

		void Render();

		static Scene& Get() { static Scene instance; return instance; }

	private:
		unsigned int _ParticleBufferID = 0;
		std::vector<Particle> _Particles;

		std::shared_ptr<VertexArray> _VertexArray;
		std::shared_ptr<Shader> _Shader;
	};
}

