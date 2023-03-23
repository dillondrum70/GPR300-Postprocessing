#ifndef COLOR_BUFFER_H
#define COLOR_BUFFER_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "imgui.h"

class ColorBuffer
{
public:

	void Create(int screenWidth, int screenHeight);
	void Copy(unsigned int tex, glm::vec2 dimensions) { texture = tex; screenDimensions = dimensions; }
	void Destroy();

	unsigned int GetTexture() { return texture; }
	glm::vec2 GetDimensions() { return screenDimensions; }

private:

	unsigned int texture;
	glm::vec2 screenDimensions;
};

#endif
