#include "ResourceManager.h"
#include <cassert>

rsm::ResourceManager::ResourceManager(dtli::DataLoaderInterface *dataLoader) : _dataLoader(dataLoader) 
{
	if (dataLoader == nullptr)
	{
		_dataLoader = new DataLoader();
		deleteDataLoader = true;
	}
	else
	{
		deleteDataLoader = false;
	}
}

void rsm::ResourceManager::setShadersDir(const std::string &dir)
{
	_shadersDir = dir;
}

shd::Shader &rsm::ResourceManager::getShader(const std::string &name)
{
	auto it = _shaders.find(name);

	assert(it != _shaders.end() && ("ResoueceManager hasn't shader with name:" + name).c_str());

	return *(it->second);
}

void rsm::ResourceManager::createShader(const std::string &name, const std::string &vName, const std::string &fName, const std::string &gName)
{
	shd::Shader *ptr;

	if (gName != hlp::nullstr)
		ptr = new shd::Shader(_dataLoader->loadTextFile(_shadersDir + vName), _dataLoader->loadTextFile(_shadersDir + fName), _dataLoader->loadTextFile(_shadersDir + gName));
	else
		ptr = new shd::Shader(_dataLoader->loadTextFile(_shadersDir + vName), _dataLoader->loadTextFile(_shadersDir + fName));

	auto it = _shaders.find(name);

	assert(it == _shaders.end() && ("ResoueceManager already has shader with name:" + name).c_str());

	_shaders[name] = ptr;
}

void rsm::ResourceManager::setImagesDir(const std::string &dir)
{
	_imagesDir = dir;
}

void rsm::ResourceManager::setXmlsDir(const std::string &dir)
{
	_xmlsDir = dir;
}

void rsm::ResourceManager::createAtlas(const std::string &name, const std::string &imageName, const std::string &xmlName)
{
	atlas::TextureAtlas *atlasPtr = new atlas::TextureAtlas(_dataLoader->loadImage(_imagesDir + imageName), _dataLoader->loadXmlData(_xmlsDir + xmlName).getData());

	auto it = _atlases.find(name);

	assert(it == _atlases.end() && ("ResoueceManager already has atlas with name:" + name).c_str());

	_atlases[name] = atlasPtr;
}

atlas::TextureAtlas &rsm::ResourceManager::getAtlas(const std::string &name)
{
	auto it = _atlases.find(name);

	assert(it != _atlases.end() && ("ResoueceManager hasn't shader with name:" + name).c_str());

	return *(it->second);
}

rsm::ResourceManager::~ResourceManager()
{
	for (auto ptr : _shaders)
		delete ptr.second;

	if(deleteDataLoader)
		delete _dataLoader;
}