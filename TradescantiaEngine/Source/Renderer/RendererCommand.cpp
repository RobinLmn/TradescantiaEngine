#include "tscpch.h"
#include "RenderCommand.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace TradescantiaEngine
{
	RendererAPI* RenderCommand::_RendererAPI = new OpenGLRendererAPI;
}