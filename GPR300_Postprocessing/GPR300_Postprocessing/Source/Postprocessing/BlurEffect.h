#ifndef BLUR_EFFECT_H
#define BLUR_EFFECT_H

#include "PostprocessEffect.h"

#include "ColorBuffer.h"

#include "../EW/Mesh.h"

class FramebufferObject;

class BlurEffect : public PostprocessEffect
{
public:

	BlurEffect(Shader* shader, std::string name, ew::Mesh* quadMesh);
	~BlurEffect();

	void ExposeImGui() override;

	void SetupShader(const std::vector<unsigned int>& colorBuffers) override;

	void SetParent(FramebufferObject* parent) override;

	unsigned int Blur(unsigned int colorBuffer);

protected:

	std::vector<FramebufferObject*> blurFbos;
	ColorBuffer blurBuffers[2];

	ew::Mesh* _quadMesh;

	int _samples = 5;
	float _blurStrength = 1;

	
};

#endif
