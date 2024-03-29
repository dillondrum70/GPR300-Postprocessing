#include "BloomEffect.h"

#include "GLFW/glfw3.h"

#include "FramebufferObject.h"

BloomEffect::BloomEffect(Shader* shader, std::string name, BlurEffect* blurEffect) : PostprocessEffect(shader, name)
{ 
	_blurEffect = blurEffect; 
	blurEffect->SetExtraPass(false);

	//blurBuffer = ColorBuffer();
	//secondBuffer = ColorBuffer();

	//fboBlur = new FramebufferObject();
	
	//glGenFramebuffers(2, blurFbos);
}

void BloomEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();
	
	_blurEffect->ExposeImGui();
}


void BloomEffect::SetupShader(const std::vector<unsigned int>& colorBuffers)
{
	bool horizontal;
	unsigned int tex = _blurEffect->Blur(colorBuffers[1], horizontal);

	//Base color map
	glActiveTexture(GL_TEXTURE0 + colorBuffers[0]);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

	//Blurred brightness map
	glActiveTexture(GL_TEXTURE0 + tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

	//Set sampler2Ds for bloom shader
	_shader->use();
	_shader->setInt("_ColorTex", colorBuffers[0]);
	_shader->setInt("_BlurredBrightTex", tex);

	//Bind default buffer so the next draw goes to the screen
	_parent->Unbind(_parent->GetDimensions());
}


void BloomEffect::SetParent(FramebufferObject* parent)
{
	PostprocessEffect::SetParent(parent);

	_blurEffect->SetParent(parent);
}