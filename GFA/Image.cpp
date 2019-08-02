#include "Image.h"
#include "stb_image.h"
#include <iostream>

Image::Image(const std::string &path)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, components;

	_data = stbi_load(path.c_str(), &width, &height, &components, 0);

	_width = width;
	_height = height;
	_colorComponents = components;
}

Image::Image(Image &&image)
{
	if (&image != this)
	{
		moveImage(std::move(image));
	}
}

Image &Image::operator=(Image &&image)
{
	if (&image != this)
	{
		moveImage(std::move(image));
	}

	return *this;
}

void Image::moveImage(Image &&image)
{
	_data = image._data;
	image._data = nullptr;
	_width = image._width;
	_height = image._height;
	_colorComponents = image._colorComponents;
}

const unsigned char *Image::getImage()
{
	return _data;
}

GLuint Image::getWidth()
{
	return _width;
}

GLuint Image::getHeight()
{
	return _height;
}

GLuint Image::getColorComponents()
{
	return _colorComponents;
}

Image::~Image()
{
	stbi_image_free(_data);
}