#include "XmlReader.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>


std::vector<atlas::texture_data> XmlReader::read(const std::string &path)
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
	
	return std::move(data);
}

std::string XmlReader::in_quotes(const std::string &str)
{
	std::size_t val_begin = str.find('\"') + 1;
	std::size_t val_end = str.find('\"', val_begin) - 1;
	std::size_t val_size = val_end - val_begin + 1;
	std::string val = str.substr(val_begin, val_size);

	return std::move(val);
}