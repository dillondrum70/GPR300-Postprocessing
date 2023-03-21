#ifndef BLOOM_EFFECT_H
#define BLOOM_EFFECT_H

#include "PostprocessEffect.h"

class BloomEffect : public PostprocessEffect
{
public:

	BloomEffect(Shader* shader, std::string name) : PostprocessEffect(shader, name) {};

	void ExposeImGui() override;

	void SetupShader(const std::vector<unsigned int>& colorBuffers) override;

protected:

	
};

#endif
