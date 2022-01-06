#pragma once
#include "Renderer/Shader.h"

// From https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h

namespace TradescantiaEngine
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const char* vertexPath, const char* fragmentPath);
        virtual ~OpenGLShader() = default;

        virtual void Use() override;

        virtual void SetBool(const std::string& name, bool value) const override;
        virtual void SetInt(const std::string& name, int value) const override;
        virtual void SetFloat(const std::string & name, float value) const override;
        virtual void SetFloat3(const std::string & name, glm::vec3 value) const override;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) const override;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
    };
}