#pragma once
#include <string>
#include <glad/glad.h>


class Image {
public:
	Image(const std::string &path);
	Image(Image &&image);
	Image &operator=(Image &&image);
	const unsigned char *getImage();
	GLuint getWidth();
	GLuint getHeight();
	GLuint getColorComponents();
	~Image();
private:
	Image(const Image &image);
	Image &operator=(const Image &image);
	void moveImage(Image &&image);
	unsigned char *_data;
	GLuint _width;
	GLuint _height;
	GLuint _colorComponents;
};