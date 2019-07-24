#pragma once
#include "DataLoaderInterface.h"

class DataLoader : public dtli::DataLoaderInterface {
public:
	dtli::image_data &loadImage(const std::string &path);
	std::string loadFile(const std::string &path);
};