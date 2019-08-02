#include "SpriteRenderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(atlas::TextureAtlas *tAtlas, shd::Shader *shader)
{
	_tAtlas = tAtlas;
	_shader = shader;

	glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);

	_shader->setUniformMat4("projection", projection);

	createVAO();
}

void SpriteRenderer::draw(const std::string &tname, glm::vec2 pos, glm::vec2 size, glm::vec3 color, GLfloat rotate)
{
	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(pos.x, pos.y, 0.0f));
	model = glm::rotate(model, glm::radians(-rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-size.x * 0.5f, -size.y * 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

	_shader->setUniformMat4("model", model);
	_shader->setUniformMat3("texMatrix", _tAtlas->getTextureMatrix(tname));
	_shader->setUniformVec3("color", color);

	_tAtlas->bind();

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void SpriteRenderer::createVAO()
{
	GLuint VBO = 0;

	GLfloat vertices[]{
	0.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
	};

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(_VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
