#include "PostprocessEffect.h"

#include "FramebufferObject.h"

PostprocessEffect::PostprocessEffect(Shader* shader, std::string name)
{
	_shader = shader;
	_name = name;
}


void PostprocessEffect::ExposeImGui()
{
	ImGui::Text(_name.c_str());
}

void PostprocessEffect::SetupShader(const std::vector<unsigned int>& colorBuffers)
{
	_shader->use();
	_shader->setInt("_ColorTex", colorBuffers[0]);
}