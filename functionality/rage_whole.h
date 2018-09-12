#pragma once
#include "../util/functionality.h"

class WholeRepeat {
private:
	std::map<int64_t, unsigned int> repeat_time;
	string LastMsg;
public:
	WholeRepeat() = default;
	string stopWholeRepeat(const int64_t group, const std::string msg);
	~WholeRepeat() = default;
};
