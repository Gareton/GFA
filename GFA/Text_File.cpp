#include "Text_File.h"
#include <fstream>
#include <sstream>

TextFile::TextFile(const std::string &path) : _raw_data(nullptr)
{
	std::ifstream input;
	std::stringstream dataStream;

	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	bool failure = false;

	try {
		input.open(path);

		dataStream << input.rdbuf();

		input.close();
	}

	catch (std::ifstream::failure &e)
	{
		failure = true;
	}

	if (!failure)
	{
		_data = std::move(dataStream.str());
		_raw_data = _data.c_str();
	}
}

TextFile::TextFile(TextFile &&tfile)
{
	move(tfile);
}

TextFile &TextFile::operator=(TextFile &&tfile)
{
	move(tfile);

	return *this;
}

void TextFile::move(TextFile &tfile)
{
	this->_data = std::move(tfile._data);
	this->_raw_data = this->_data.c_str();
}

const char *TextFile::getText()
{
	return _raw_data;
}

TextFile::~TextFile() {}