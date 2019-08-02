#pragma once
#include <string>
#include <glad/glad.h>
#include "Image.h"
#include "Text_File.h"
#include "XmlData.h"

namespace dtli {

	class LoadingFailure {
	public:
		LoadingFailure(const std::string &path) { _path = path; }
		std::string getPath() { return _path; }
	private:
		std::string _path;
	};

	class DataLoaderInterface {
	public:
		virtual Image loadImage(const std::string &path) = 0;
		virtual TextFile loadTextFile(const std::string &path) = 0;
		virtual XmlData loadXmlData(const std::string &path) = 0;
	};

}