#include "BlurEffect.h"

#include "GLFW/glfw3.h"

void BlurEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();

	ImGui::SliderFloat("Blur Strength", &_blurStrength, 0, 10);
	ImGui::Checkbox("Horizontal", &_horizontal);
}


void BlurEffect::SetupShader(const std::vector<unsigned int>& colorBuffers)
{
	PostprocessEffect::SetupShader(colorBuffers);

	_shader->setFloat("_BlurStrength", _blurStrength);
	_shader->setInt("horizontal", _horizontal);
}