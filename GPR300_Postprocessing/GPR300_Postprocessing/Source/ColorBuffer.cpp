#include "ColorBuffer.h"

void ColorBuffer::Create(int screenWidth, int screenHeight)
{
	Destroy();

	screenDimensions = glm::vec2(screenWidth, screenHeight);

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenWidth, screenHeight, 0, GL_RGBA, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ColorBuffer::Destroy()
{
	glDeleteTextures(1, &texture);
}