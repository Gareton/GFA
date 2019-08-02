#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Image.h"

class Texture2D {
public:
	Texture2D(Image image, GLenum internal_format = GL_RGBA, GLenum wrap_s = GL_REPEAT, GLenum wrap_t = GL_REPEAT);
	void bind();
	GLuint getID();
	glm::vec2 getSize();
	~Texture2D();
private:
	GLenum image_format(GLuint colorComponents);

	GLuint _id;
	GLuint _width;
	GLuint _height;
};