#include "Texture.h"

Texture2D::Texture2D(Image image, GLenum internal_format, GLenum wrap_s, GLenum wrap_t)
	:_width(image.getWidth()), _height(image.getHeight())
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _width, _height, 0, image_format(image.getColorComponents()), GL_UNSIGNED_BYTE, image.getImage());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

GLuint Texture2D::getID()
{
	return _id;
}

glm::vec2 Texture2D::getSize()
{
	return glm::vec2(_width, _height);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_id);
}

GLenum Texture2D::image_format(GLuint colorComponents)
{
	switch (colorComponents)
	{
		case 4: return GL_RGBA;
		case 3: return GL_RGB;
		case 1: return GL_RED;
	}

	return GL_RGB;
}