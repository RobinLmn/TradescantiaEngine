#pragma once
#include "Entity.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

namespace TradescantiaEngine
{
	class Scene
	{
	private:
		Scene() = default;

	public:
		~Scene();
		Scene(Scene const&) = delete;
		Scene operator=(Scene const&) = delete;

		void StartScene();

		void AddParticles(Particle* particles, const int count);
		Particle* GetParticle() const { return _Particles; }
		int GetCount() const { return _Count; }

		void Render();

		static Scene& Get() { static Scene instance; return instance; }

	private:
		Particle* _Particles = nullptr;
		int _Count = 0;

		std::shared_ptr<VertexArray> _VertexArray;
		std::shared_ptr<Shader> _Shader;
		float* _Vertices = nullptr;
	};
}

