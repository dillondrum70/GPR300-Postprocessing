#include "TextureManager.h"

TextureManager::TextureManager()
{
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		textures[i] = Texture(GL_TEXTURE0 + i, GL_TEXTURE0 + (i + MAX_TEXTURES));
	}
}

Texture TextureManager::AddTexture(const char* texFilePath, const char* normFilePath)
{
	textures[textureCount] = Texture(GL_TEXTURE0 + textureCount, GL_TEXTURE0 + (textureCount + MAX_TEXTURES));
	textures[textureCount].CreateTexture(texFilePath, normFilePath);
	glActiveTexture(textures[textureCount].texNumber);
	glBindTexture(GL_TEXTURE_2D, textures[textureCount].GetTexture());

	glActiveTexture(textures[textureCount].normNumber);
	glBindTexture(GL_TEXTURE_2D, textures[textureCount].GetNormalMap());

	textureCount++;

	return textures[textureCount - 1];
}