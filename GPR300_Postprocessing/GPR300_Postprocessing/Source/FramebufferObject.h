#ifndef FRAMEBUFFER_OBJECT_H
#define FRAMEBUFFER_OBJECT_H

#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "imgui.h"

#include "ColorBuffer.h"
#include "DepthBuffer.h"

#include "Postprocessing/PostprocessEffect.h"
#include "Postprocessing/GrayscaleEffect.h"

class FramebufferObject
{
public:

	FramebufferObject();

	unsigned int GetId() { return id; }
	bool IsComplete();

	void Create();
	void AddColorAttachment(ColorBuffer& buffer, GLenum attachmentNum);
	void AddDepthAttachment(DepthBuffer& buffer);
	void Bind();
	void Unbind(glm::vec2 viewportDimensions);
	void Clear(glm::vec3 clearColor);
	void Destroy();

	void ExposeImGui();

	void AddEffect(PostprocessEffect& effect);

	void SetupShader(unsigned int colorBuffer);

private:

	unsigned int id;
	glm::vec2 screenDimensions;

	int currentEffect = 0;
	std::vector<PostprocessEffect> postprocessEffects;
};

#endif