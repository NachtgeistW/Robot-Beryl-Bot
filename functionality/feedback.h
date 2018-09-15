#pragma once
#include "../util/util.h"
class feedback
{
public:
	feedback() = default;
	string fb_in_group(int64_t group, int64_t qq, string msg);
	string fb_in_privt(int64_t qq, string msg);
	~feedback() = default;

private:
	string group = "(\\[CQ:at,qq=)(" + util::int64_ttos(util::Beryl) + ")(\\])(.*)(反馈|告诉你主人)(.*)";
	string privt = "(反馈|告诉你主人)(.*)";
	std::smatch match;
};
