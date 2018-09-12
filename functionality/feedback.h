#pragma once
#include "../util/functionality.h"
class feedback
{
public:
	feedback();
	~feedback() = default;
	string fb_in_group(int64_t group, int64_t qq, string msg);
	string fb_in_privt(int64_t qq, string msg);

private:
	std::regex group;
	std::regex privt;
	std::smatch match;
};

feedback::feedback()
{
	group = "([CQ:at,qq=)([1-9][0-9]{4,})(])(反馈|告诉你主人)(.*?)";
	privt = "(反馈|告诉你主人)(.*?)";
}