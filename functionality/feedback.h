#pragma once
#include "../util/util.h"
class Feedback
{
public:
	Feedback() = default;
	string fb_in_group(int64_t group, int64_t qq, string msg);
	string FbInPrivt(int64_t qq, string msg);
	~Feedback() = default;

private:
	string group = "(\\[CQ:at,qq=)(" + util::int64_ttos(util::Beryl) + ")(\\])(.*)(反馈|告诉你主人)(.*)";
	string privt = "(反馈|告诉你主人)(.*)";
	std::smatch match;
};
