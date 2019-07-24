#include "DataLoader.h"
#include "stb_image.h"
#include <iostream>
#include <fstream>
#include <sstream>

dtli::image_data &DataLoader::loadImage(const std::string &path)
{
	dtli::image_data invalid;

	return invalid;
}


std::string DataLoader::loadFile(const std::string &path)
{
	std::ifstream input;
	std::stringstream dataStream;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		input.open(path);

		dataStream << input.rdbuf();

		input.close();
	}

	catch (std::ifstream::failure e)
	{
		throw(dtli::LoadingFailure(path));
	}

	return dataStream.str();
}