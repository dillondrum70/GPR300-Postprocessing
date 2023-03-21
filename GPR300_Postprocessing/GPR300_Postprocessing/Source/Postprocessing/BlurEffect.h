#ifndef BLUR_EFFECT_H
#define BLUR_EFFECT_H

#include "PostprocessEffect.h"

class BlurEffect : public PostprocessEffect
{
public:

	BlurEffect(Shader* shader, std::string name) : PostprocessEffect(shader, name) {};

	void ExposeImGui() override;

	void SetupShader(const std::vector<unsigned int>& colorBuffers) override;

protected:

	float _blurStrength = 1;
	bool _horizontal = false;
};

#endif