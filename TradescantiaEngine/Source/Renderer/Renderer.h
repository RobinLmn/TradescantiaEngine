#pragma once
#include "VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Camera.h"

namespace TradescantiaEngine
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& Camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader, const int ParticleBufferID, const std::shared_ptr<VertexArray>& vertexArray, const int count);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData& GetSceneData() { static SceneData sceneData; return sceneData; }
	};
}