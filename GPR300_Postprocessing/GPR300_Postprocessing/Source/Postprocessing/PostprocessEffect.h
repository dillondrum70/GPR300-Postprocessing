#ifndef POSTPROCESS_EFFECT_H
#define POSTPROCESS_EFFECT_H

#include "../EW/Shader.h"

#include "imgui.h"

class PostprocessEffect
{
public:

	PostprocessEffect(Shader* shader, std::string name);

	virtual void ExposeImGui();

	virtual void SetupShader(unsigned int colorBuffer);
	
	Shader* GetShader() { return _shader; }
	std::string GetName() { return _name; }

protected:

	Shader* _shader;
	std::string _name;

private:
};

#endif