#ifndef BLOOM_EFFECT_H
#define BLOOM_EFFECT_H

#include "PostprocessEffect.h"
#include "BlurEffect.h"
#include "ColorBuffer.h"

#include "../EW/Mesh.h"

class FramebufferObject;

class BloomEffect : public PostprocessEffect
{
public:

	BloomEffect(Shader* shader, std::string name, ew::Mesh* quadMesh, BlurEffect* blurEffect);
	~BloomEffect();

	void ExposeImGui() override;

	void SetupShader(const std::vector<unsigned int>& colorBuffers) override;

	void SetParent(FramebufferObject* parent) override;

protected:

	ew::Mesh* _quadMesh;

	BlurEffect* _blurEffect;

	ColorBuffer blurBuffer;
	//ColorBuffer secondBuffer;	//We can use this to make several blur passes

	//Must be a dynamic pointer object since undefined with foward declaration, otherwise we need to create a new one every frame
	//FramebufferObject* fboBlur;
};

#endif
