#include "FramebufferObject.h"

#include "../EW/Shader.h"
#include "../EW/ShapeGen.h"

FramebufferObject::FramebufferObject()
{
	id = 0;

	screenDimensions = glm::vec2(0, 0);
}

bool FramebufferObject::IsComplete()
{
	Bind();

	return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void FramebufferObject::Create()
{
	glGenFramebuffers(1, &id);

	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

/// <summary>
/// Adds a color attachment to the Framebuffer object
/// </summary>
/// <param name="buffer">Color buffer to add</param>
/// <param name="attachmentNum">GL_COLOR_ATTACHMENT<0-8></param>
void FramebufferObject::AddColorAttachment(ColorBuffer& buffer, GLenum attachmentNum)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentNum, GL_TEXTURE_2D, buffer.GetTexture(), 0);

	screenDimensions = buffer.GetDimensions();
}


void FramebufferObject::AddDepthAttachment(DepthBuffer& buffer)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buffer.GetRenderBuffer());
}

void FramebufferObject::Bind()
{
	glViewport(0, 0, screenDimensions.x, screenDimensions.y);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glEnable(GL_DEPTH_TEST);
}


void FramebufferObject::Unbind(glm::vec2 viewportDimensions)
{
	glViewport(0, 0, viewportDimensions.x, viewportDimensions.y);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
}


void FramebufferObject::Clear(glm::vec3 clearColor)
{
	Bind();

	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void FramebufferObject::Destroy()
{
	glDeleteFramebuffers(1, &id);
}