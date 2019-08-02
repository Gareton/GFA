#pragma once
#include "TextureAtlas.h"
#include <vector>

class XmlReader {
public:
	std::vector<atlas::texture_data> read(const std::string &path);
private:
	std::string in_quotes(const std::string &str);
};