#include "tscpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace TradescantiaEngine
{
	void Renderer::BeginScene(Camera& camera)
	{
		GetSceneData().ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Use();
		shader->SetMat4("u_ViewProjection", GetSceneData().ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}