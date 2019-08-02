#pragma once
#include <string>
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Helper.h"
#include <map>
#include "Image.h"

namespace atlas {
	struct texture_data {
		texture_data(const std::string &Name = hlp::nullstr, GLuint X_offset = 0, GLuint Y_offset = 0, GLuint Width = 0, GLuint Height = 0)
			: name(Name), x_offset(X_offset), y_offset(Y_offset), width(Width), height(Height)
		{}

		std::string name;
		GLuint x_offset;
		GLuint y_offset;
		GLuint width;
		GLuint height;
	};

	struct placement_data {
		placement_data(GLuint X_offset = 0, GLuint Y_offset = 0, GLuint Width = 0, GLuint Height = 0)
			: x_offset(X_offset), y_offset(Y_offset), width(Width), height(Height)
		{}

		placement_data(const texture_data &d)
		{
			x_offset = d.x_offset;
			y_offset = d.y_offset;
			width = d.width;
			height = d.height;
		}

		GLuint x_offset;
		GLuint y_offset;
		GLuint width;
		GLuint height;
	};


	class TextureAtlas {
	public:
		TextureAtlas(Image image, std::vector<atlas::texture_data> data);
		placement_data getTextureCoords(const std::string &name);
		glm::vec2 getSize();
		glm::mat3 getTextureMatrix(const std::string &name);
		void bind();
	private:
		Texture2D _atlas_texture;
		std::map<std::string, placement_data> _textures_inf;
	};
}