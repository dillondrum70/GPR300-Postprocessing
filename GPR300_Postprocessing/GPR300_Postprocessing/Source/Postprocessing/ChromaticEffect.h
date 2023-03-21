#ifndef CHROMATIC_EFFECT_H
#define CHROMATIC_EFFECT_H

#include "PostprocessEffect.h"

class ChromaticEffect : public PostprocessEffect
{
public:

	ChromaticEffect(Shader* shader, std::string name) : PostprocessEffect(shader, name) {};

	void ExposeImGui() override;

	void SetupShader(unsigned int colorBuffer) override;

protected:

	float _aberrationAmount = 0.01f;
};

#endif
