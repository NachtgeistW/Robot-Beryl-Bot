#pragma once
#include "../util/util.h"
class At
{
public:
	At() = default;
	string select_reply(void);
	void only_being_at(int64_t group, string msg);
	~At() = default;

private:
	string at = "(\\[CQ:at,qq=)(" + util::int64_ttos(util::Beryl) + ")(\\])(.)";
};
