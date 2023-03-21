#include "EdgeDetectEffect.h"

void EdgeDetectEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();

	ImGui::SliderFloat("Sample Distance", &_sampleDist, -.01f, .01f);
	ImGui::SliderFloat("Edge Threshold", &_threshold, 0.f, 1.f);
}


void EdgeDetectEffect::SetupShader(unsigned int colorBuffer)
{
	PostprocessEffect::SetupShader(colorBuffer);

	_shader->setFloat("_SampleDist", _sampleDist);
	_shader->setFloat("_Threshold", _threshold);
}