#include "DataLoader.h"

Image DataLoader::loadImage(const std::string &path)
{
	Image image(path);

	if (image.getImage() == nullptr)
		throw dtli::LoadingFailure(path);

	return std::move(image);
}

TextFile DataLoader::loadTextFile(const std::string &path)
{
	TextFile tfile(path);

	if (tfile.getText() == nullptr)
		throw dtli::LoadingFailure(path);

	return std::move(tfile);
}

XmlData DataLoader::loadXmlData(const std::string &path)
{
	XmlData xml_data(path);

	if (xml_data.getData().size() == 0)
		throw dtli::LoadingFailure(path);

	return std::move(xml_data);
}
