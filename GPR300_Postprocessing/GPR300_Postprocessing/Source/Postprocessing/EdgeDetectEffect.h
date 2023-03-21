#ifndef EDGE_DETECT_EFFECT_H
#define EDGE_DETECT_EFFECT_H

#include "PostprocessEffect.h"

class EdgeDetectEffect : public PostprocessEffect
{
public:

	EdgeDetectEffect(Shader* shader, std::string name) : PostprocessEffect(shader, name) {};

	void ExposeImGui() override;

	void SetupShader(unsigned int colorBuffer) override;

protected:

	float _sampleDist = 0.001f;
	float _threshold = .1f;
};

#endif
