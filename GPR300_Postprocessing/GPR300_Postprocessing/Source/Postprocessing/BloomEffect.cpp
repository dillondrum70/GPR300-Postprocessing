#include "BloomEffect.h"

#include "GLFW/glfw3.h"

#include "FramebufferObject.h"

BloomEffect::BloomEffect(Shader* shader, std::string name, ew::Mesh* quadMesh, BlurEffect* blurEffect) : PostprocessEffect(shader, name)
{ 
	_quadMesh = quadMesh; 
	_blurEffect = blurEffect; 

	blurBuffer = ColorBuffer();
	//secondBuffer = ColorBuffer();

	//fboBlur = new FramebufferObject();
}

BloomEffect::~BloomEffect()
{
	/*if (fboBlur)
	{
		delete fboBlur;
	}
	
	fboBlur = nullptr;*/
}

void BloomEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();

	_blurEffect->ExposeImGui();
}


void BloomEffect::SetupShader(const std::vector<unsigned int>& colorBuffers)
{
	//PostprocessEffect::SetupShader(colorBuffers);
	
	/*_shader->use();
	_shader->setInt("_ColorTex", colorBuffers[1]);

	return;*/
	
	FramebufferObject fboBlur;
	fboBlur.Create();
	fboBlur.AddColorAttachment(blurBuffer, GL_COLOR_ATTACHMENT0);
	//fboBlur->AddColorAttachment(secondBuffer, GL_COLOR_ATTACHMENT1);
	fboBlur.AddEffect(_blurEffect);

	//Check if FramebufferObject for blurring the second color buffer is complete
	if (!fboBlur.IsComplete())
	{
		printf("Blur FramebufferObject in BloomEffect is not complete.");
		return;
	}

	//Bind the blur framebuffer and clear it
	fboBlur.Bind();
	fboBlur.Clear(glm::vec3(0, 0, 0));

	//Texture passed in as _ColorTex that blur effect samples
	glActiveTexture(GL_TEXTURE0 + colorBuffers[1]);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

	//Setup the blur shader and draw the fullscreen quad, blurring the second color buffer with bright objects
	fboBlur.Bind();
	fboBlur.SetupShader();
	_blurEffect->GetShader()->setInt("_ColorTex", colorBuffers[1]);	//override the blur effect's original _ColorTex to be the brightness buffer
	_quadMesh->draw();

	//_parent->Bind();

	//Color data read from the blur effect, fed into the bloom shader as _BlurredBrightTex
	glActiveTexture(GL_TEXTURE0 + blurBuffer.GetTexture());
	glBindTexture(GL_TEXTURE_2D, blurBuffer.GetTexture());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

	//Original Texture, fed into bloom shader as _ColorTex to have _BlurredBrightTex added to it
	glActiveTexture(GL_TEXTURE0 + colorBuffers[0]);
	glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	
	//Bind the base color buffer
	_shader->use();
	_shader->setInt("_ColorTex", colorBuffers[0]);
	_shader->setInt("_BlurredBrightTex", blurBuffer.GetTexture());

	//Apply blur to colorBuffers[1]

	//Pass in colorBuffers[1] to bloom.frag as a uniform sampler2D

	//In bloom.frag, sample the _ColorTex and bloom texture then add them

	fboBlur.Destroy();

	//_parent->Bind();
}


void BloomEffect::SetParent(FramebufferObject* parent)
{
	PostprocessEffect::SetParent(parent);

	blurBuffer.Create(_parent->GetDimensions().x, _parent->GetDimensions().y);

	//firstBuffer.Create(_parent->GetDimensions().x, _parent->GetDimensions().y);

	////secondBuffer.Create(_parent->GetDimensions().x, _parent->GetDimensions().y);


	//fboBlur->Create();
	//fboBlur->AddColorAttachment(firstBuffer, GL_COLOR_ATTACHMENT0);
	////fboBlur->AddColorAttachment(secondBuffer, GL_COLOR_ATTACHMENT1);
	//fboBlur->AddEffect(_blurEffect);
}