#pragma once
#include "DataLoaderInterface.h"

class DataLoader : public dtli::DataLoaderInterface {
public:
	Image loadImage(const std::string &path);
	TextFile loadTextFile(const std::string &path);
	XmlData loadXmlData(const std::string &path);
};