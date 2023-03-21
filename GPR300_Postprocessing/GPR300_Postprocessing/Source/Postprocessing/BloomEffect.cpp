#include "BloomEffect.h"

#include "GLFW/glfw3.h"

#include "FramebufferObject.h"

void BloomEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();

	
}


void BloomEffect::SetupShader(const std::vector<unsigned int>& colorBuffers)
{
	PostprocessEffect::SetupShader(colorBuffers);

	ColorBuffer firstBuffer;
	firstBuffer.Create(parent->GetDimensions().x, parent->GetDimensions().y);

	ColorBuffer secondBuffer;
	secondBuffer.Create(parent->GetDimensions().x, parent->GetDimensions().y);

	FramebufferObject fbo;
	fbo.Create();
	fbo.AddColorAttachment(firstBuffer, GL_COLOR_ATTACHMENT0);
	fbo.AddColorAttachment(firstBuffer, GL_COLOR_ATTACHMENT1);

	fbo.Bind();

	//Apply blur to colorBuffers[1]

	//Pass in colorBuffers[1] to bloom.frag as a uniform sampler2D

	//In bloom.frag, sample the _ColorTex and bloom texture then add them
	
}