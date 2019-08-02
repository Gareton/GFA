#include "XmlData.h"
#include <iterator>
#include <fstream>
#include <iostream>

XmlData::XmlData(const std::string &path)
{
	std::ifstream in(path);
	std::istream_iterator<std::string> iter(in);
	std::istream_iterator<std::string> eos;

	while (iter != eos)
	{
		if (*iter == "<sprite")
			break;

		++iter;
	}

	std::vector<atlas::texture_data> data;

	while (iter != eos && *iter != "</TextureAtlas>")
	{
		++iter;

		atlas::texture_data td;

		td.name = in_quotes(*iter);
		++iter;
		td.x_offset = stoi(in_quotes(*iter));
		++iter;
		td.y_offset = stoi(in_quotes(*iter));
		++iter;
		td.width = stoi(in_quotes(*iter));
		++iter;
		td.height = stoi(in_quotes(*iter));
		++iter;

		data.push_back(td);
	}

	_data = std::move(data);
}

XmlData::XmlData(XmlData &&data)
{
	this->move(data);
}

XmlData &XmlData::operator=(XmlData &&data)
{
	this->move(data);

	return *this;
}

void XmlData::move(XmlData &data)
{
	this->_data = std::move(data._data);
}

XmlData::~XmlData() { }

std::vector<atlas::texture_data> &XmlData::getData()
{
	return _data;
}

std::string XmlData::in_quotes(const std::string &str)
{
	std::size_t val_begin = str.find('\"') + 1;
	std::size_t val_end = str.find('\"', val_begin) - 1;
	std::size_t val_size = val_end - val_begin + 1;
	std::string val = str.substr(val_begin, val_size);

	return std::move(val);
}