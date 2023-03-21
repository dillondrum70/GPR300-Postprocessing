#include "ChromaticEffect.h"

void ChromaticEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();

	ImGui::SliderFloat("Aberration Amount", &_aberrationAmount, -.1f, .1f);
}


void ChromaticEffect::SetupShader(unsigned int colorBuffer)
{
	PostprocessEffect::SetupShader(colorBuffer);

	_shader->setFloat("_AberrationAmount", _aberrationAmount);
}