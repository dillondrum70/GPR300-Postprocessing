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
	
	//glGenFramebuffers(2, blurFbos);

	//Create temp fbos
	for (int i = 0; i < 2; i++)
	{
		FramebufferObject* fbo = new FramebufferObject();
		fbo->Create();
		blurFbos.push_back(fbo);
	}
}

BloomEffect::~BloomEffect()
{
	//Delete temp fbos
	for (int i = blurFbos.size() - 1; i >= 0; i--)
	{
		if (blurFbos[i] != nullptr)
		{
			delete blurFbos[i];
			blurFbos[i] = nullptr;
		}
	}

	blurFbos.clear();
}

void BloomEffect::ExposeImGui()
{
	PostprocessEffect::ExposeImGui();

	ImGui::SliderInt("Samples", &_samples, 1, 10);
	ImGui::SliderFloat("Blur Strength", &_blurStrength, 1, 10);
	
	//_blurEffect->ExposeImGui();
}


void BloomEffect::SetupShader(const std::vector<unsigned int>& colorBuffers)
{
	//Attach temp color buffers to temp fbos
	for (unsigned int i = 0; i < 2; i++)
	{
		blurFbos[i]->Bind();
		blurFbos[i]->AddColorAttachment(blurBuffers[i], GL_COLOR_ATTACHMENT0);
	}

	//Use blur shader
	unsigned int tex = colorBuffers[1];
	bool horizontal = true;
	_blurEffect->GetShader()->use();
	_blurEffect->GetShader()->setFloat("_BlurStrength", _blurStrength);
	for (unsigned int i = 0; i < _samples; i++)
	{
		//Bind current fbo
		blurFbos[horizontal]->Bind();
		
		//Bind last texture drawn to
		glBindTexture(GL_TEXTURE_2D, tex);

		//Shader variables and draw
		_blurEffect->GetShader()->setInt("horizontal", horizontal);
		_blurEffect->GetShader()->setInt("_ColorTex", tex);
		_quadMesh->draw();

		//Switch blur direction for next pass
		horizontal = !horizontal;

		//Set texture to sample from in next step (whether another blur or bloom)
		tex = blurBuffers[!horizontal].GetTexture();
	}

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
	_shader->setInt("_BlurredBrightTex", blurBuffers[horizontal].GetTexture());

	//Bind default buffer so the next draw goes to the screen
	_parent->Unbind(_parent->GetDimensions());
}


void BloomEffect::SetParent(FramebufferObject* parent)
{
	PostprocessEffect::SetParent(parent);

	//Create buffers based on parent dimensions
	for (int i = 0; i < 2; i++)
	{
		blurBuffers[i].Create(_parent->GetDimensions().x, _parent->GetDimensions().y);
	}
}