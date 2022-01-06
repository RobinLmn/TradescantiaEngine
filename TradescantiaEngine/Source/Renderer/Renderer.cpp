#include "tscpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

// TEMP
#include "glad/glad.h"

namespace TradescantiaEngine
{
	void Renderer::BeginScene(Camera& camera)
	{
		GetSceneData().ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Buffer>& particleBuffer, const std::shared_ptr<VertexArray>& vertexArray, const int count)
	{
		ZoneScoped
		shader->Use();
		shader->SetMat4("u_ViewProjection", GetSceneData().ViewProjectionMatrix);
		vertexArray->Bind();
		particleBuffer->BindBase();
		RenderCommand::DrawInstanced(count);
		particleBuffer->UnbindBase();
	}
}