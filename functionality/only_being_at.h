#pragma once
#include "../util/util.h"
class At
{
public:
	At() = default;
	string SelectReply(void);
	void OnlyBeingAt(int64_t group, string msg);
	~At() = default;
};
