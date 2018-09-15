#include "feedback.h"

string feedback::fb_in_group(int64_t groupID, int64_t qq, string msg)
{
	std::regex reg(group);
	string reply_to_user = "", reply_to_master = "";
	if (std::regex_match(msg, match, reg) == true)
	{
		reply_to_user = "[CQ:at,qq=" + util::int64_ttos(qq) + "] 已经告诉夜轮了，谢谢你的反馈（鞠躬）";
		reply_to_master = "The feedback from member " + util::int64_ttos(qq)
			+ " in Group " + util::int64_ttos(groupID) + ":\n" + match.str(6);
		CQ::sendPrivateMsg(util::Master, reply_to_master);
	}
	return reply_to_user;
}

string feedback::fb_in_privt(int64_t qq, string msg)
{
	std::regex reg(privt);
	string reply_to_user, reply_to_master;
	if (std::regex_match(msg, match, reg) == true)
	{
		reply_to_user = "已经告诉夜轮了，谢谢你的反馈（鞠躬）";
		reply_to_master = "The feedback from user " + util::int64_ttos(qq) + ":\n" + match.str(2);
		CQ::sendPrivateMsg(util::Master, reply_to_master);
	}
	return reply_to_user;
}
