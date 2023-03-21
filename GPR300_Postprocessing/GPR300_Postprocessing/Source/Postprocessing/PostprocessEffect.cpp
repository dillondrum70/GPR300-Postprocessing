#include "PostprocessEffect.h"

PostprocessEffect::PostprocessEffect(Shader* shader, std::string name)
{
	_shader = shader;
	_name = name;
}


void PostprocessEffect::ExposeImGui()
{
	ImGui::Text(_name.c_str());
}

void PostprocessEffect::SetupShader(unsigned int colorBuffer)
{
	_shader->use();
	_shader->setInt("_ColorTex", colorBuffer);
}