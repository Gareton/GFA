#pragma once
#include "Shader.h"
#include <map>
#include "Helper.h"
#include "DataLoaderInterface.h"
#include "DataLoader.h"
#include "TextureAtlas.h"

namespace rsm {


	class ResourceManager {
	public:
		ResourceManager(dtli::DataLoaderInterface *dataLoader = nullptr);
		void setShadersDir(const std::string &dir);
		void setImagesDir(const std::string &dir);
		void setXmlsDir(const std::string &dir);
		void createShader(const std::string &name, const std::string &vName, const std::string &fName, const std::string &gName = hlp::nullstr);
		void createAtlas(const std::string &name, const std::string &imageName, const std::string &xmlName);
		shd::Shader &getShader(const std::string &name);
		atlas::TextureAtlas &getAtlas(const std::string &name);
		~ResourceManager();
	private:
		std::map<std::string, shd::Shader *> _shaders;
		std::map<std::string, atlas::TextureAtlas *> _atlases;
		dtli::DataLoaderInterface *_dataLoader;
		std::string _shadersDir;
		std::string _imagesDir;
		std::string _xmlsDir;

		bool deleteDataLoader;
	};
}