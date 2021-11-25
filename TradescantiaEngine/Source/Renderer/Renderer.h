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
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* _SceneData;
	};
}