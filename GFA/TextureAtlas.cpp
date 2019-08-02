#include "TextureAtlas.h"
#include <glm/gtx/matrix_transform_2d.hpp>

atlas::TextureAtlas::TextureAtlas(Image image, std::vector<atlas::texture_data> data)
	:_atlas_texture(std::move(image))
{
	auto height = _atlas_texture.getSize().y;

	for (auto item : data)
		_textures_inf[item.name] = placement_data(item.x_offset, height - item.y_offset - item.height, item.width, item.height);
}

atlas::placement_data atlas::TextureAtlas::getTextureCoords(const std::string &name)
{
	return _textures_inf[name];
}

glm::mat3 atlas::TextureAtlas::getTextureMatrix(const std::string &name)
{
	auto dt = _textures_inf[name];
	glm::vec2 atlasSize = getSize();
	glm::vec2 texSize = glm::vec2(dt.width, dt.height);

	GLfloat x_scale = texSize.x / atlasSize.x;
	GLfloat y_scale = texSize.y / atlasSize.y;
	GLfloat x_translate = dt.x_offset / atlasSize.x;
	GLfloat y_translate = dt.y_offset / atlasSize.y;

	glm::mat3 translate(translate(glm::mat3(1.0f), glm::vec2(x_translate, y_translate)));
	glm::mat3 scale(glm::scale(glm::mat3(1.0f), glm::vec2(x_scale, y_scale)));

	glm::mat3 mat(translate * scale);

	return mat;
}


glm::vec2 atlas::TextureAtlas::getSize()
{
	return _atlas_texture.getSize();
}

void atlas::TextureAtlas::bind()
{
	_atlas_texture.bind();
}