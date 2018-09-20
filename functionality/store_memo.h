#pragma once
#include "../util/util.h"
using std::vector;
class SongInfo
{
private:
	std::map<string, vector<string>> Memo;

public:
	SongInfo() = default;
	~SongInfo() = default;
	bool read_chart(string path);
};
