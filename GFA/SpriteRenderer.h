#pragma once
#include "TextureAtlas.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"

class SpriteRenderer {
public:
	SpriteRenderer(atlas::TextureAtlas *tAtlas, shd::Shader *shader);
	void draw(const std::string &tname, glm::vec2 pos = glm::vec2(0.5f, 0.5f), glm::vec2 size = glm::vec2(0.1f, 0.1f), 
		      glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f), GLfloat rotate = 0.0f);
private:
	void createVAO();

	atlas::TextureAtlas *_tAtlas;
	GLuint _VAO;
	shd::Shader *_shader;
};