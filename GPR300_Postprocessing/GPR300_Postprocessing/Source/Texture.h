#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "imgui.h"

class Texture
{
private:
	GLuint texture = 0;
	GLuint normalMap = 16;

	glm::ivec2 dimensions = glm::ivec2(0);
	glm::ivec2 normDimensions = glm::ivec2(0);

	int texFileChannels = 0;
	int normFileChannels = 0;
	int desiredChannels = 0;

	GLenum format = GL_RGB;
	GLenum type = GL_UNSIGNED_BYTE;

	const char* wrapModes[4] = { "GL_REPEAT", "GL_MIRRORED_REPEAT", "GL_CLAMP_TO_EDGE", "GL_CLAMP_TO_BORDER" };
	GLint wrapEnumModes[4] = { GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER };
	int currentVertWrap = 0;
	GLint verticalWrapMode = GL_REPEAT;
	int currentHorizWrap = 0;
	GLint horizontalWrapMode = GL_REPEAT;

	//GL_LINEAR for smoother interpilation, GL_NEAREST for pixelation
	const char* filterModes[2] = { "GL_LINEAR", "GL_NEAREST" };
	GLint filterEnumModes[2] = { GL_LINEAR, GL_NEAREST };
	int currentMagFilter = 0;
	GLint magFilter = GL_LINEAR;
	int currentMinFilter = 0;
	GLint minFilter = GL_LINEAR;

	unsigned char* textureData = nullptr;
	unsigned char* normalData = nullptr;

public:
	GLenum texNumber = GL_TEXTURE0;
	GLenum normNumber = GL_TEXTURE16;

	glm::vec2 scaleFactor = glm::vec2(1);

	glm::vec2 scrollSpeed = glm::vec2(0);

	glm::vec2 offset = glm::vec2(0);

	Texture() {}

	Texture(GLenum textureNumber, GLenum normalNumber) : texNumber(textureNumber), normNumber(normalNumber) {}

	glm::ivec2 GetDimensions() { return dimensions; }
	GLuint GetTexture() { return texture; }
	GLuint GetNormalMap() { return normalMap; }

	GLuint CreateTexture(const char* texFilePath, const char* normFilePath);

	void ExposeImGui();
};

#endif