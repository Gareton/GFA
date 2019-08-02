#pragma once
#include <string>
#include <vector>
#include "TextureAtlas.h"

class XmlData {
public:
	XmlData(const std::string &path);
	XmlData(XmlData &&data);
	XmlData &operator=(XmlData &&data);
	~XmlData();
	std::vector<atlas::texture_data> &getData();
private:
	XmlData(XmlData &data);
	XmlData &operator=(XmlData &data);
	std::string in_quotes(const std::string &str);
	void move(XmlData &data);

	std::vector<atlas::texture_data> _data;
};