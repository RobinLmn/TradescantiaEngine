#include "tscpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace TradescantiaEngine
{
	Renderer::SceneData* Renderer::_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(Camera& camera)
	{
		_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Use();
		shader->SetMat4("u_ViewProjection", _SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}