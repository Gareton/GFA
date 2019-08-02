#pragma once
#include <string>

class TextFile {
public:
	TextFile(const std::string &path);
	TextFile(TextFile &&tfile);
	TextFile &operator=(TextFile &&tfile);
	const char *getText();
	~TextFile();
private:
	TextFile(TextFile &tfile);
	TextFile &operator=(TextFile &tfile);
	void move(TextFile &tfile);

	std::string _data;
	const char *_raw_data;
};