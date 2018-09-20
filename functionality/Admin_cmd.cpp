#include "Admin_cmd.h"

void reply_origin_msg(int64_t group, int64_t qq, string msg)
{
	std::regex reg("(Ô­¾äÊä³ö)(.*)");
	std::smatch match;
	if (std::regex_match(msg, match, reg) && qq == util::Master)
	{
		string reply = match[2].str();
		CQ::sendGroupMsg(group, reply);
	}
}
