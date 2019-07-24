#pragma once
#include <string>
#include <glad/glad.h>

namespace dtli {

	struct image_data {
		std::string image = "";
		GLuint colorComponents = 0;
		GLuint width = 0;
		GLuint height = 0;
	};

	class LoadingFailure {
	public:
		LoadingFailure(const std::string &path) { _path = path; }
		std::string getPath() { return _path; }
	private:
		std::string _path;
	};

	class DataLoaderInterface {
	public:
		virtual image_data &loadImage(const std::string &path) = 0;
		virtual std::string loadFile(const std::string &path) = 0;
	};

}