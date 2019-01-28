#include "feedback.h"

string Feedback::FeedbackGroup(const int64_t groupID, const int64_t qq, const string msg)
{
	std::regex reg(kgroup_regex_);
	string reply_to_user = "", reply_to_master = "";
	if (std::regex_match(msg, feedback_match_, reg) == true)
	{
		reply_to_user = "[CQ:at,qq=" + util::int64_ttos(qq) + "] 已经告诉夜轮了，谢谢你的反馈（鞠躬）";
		reply_to_master = util::int64_ttos(qq) + " in Group " + util::int64_ttos(groupID) + ":\n" + feedback_match_.str(6);
		CQ::sendPrivateMsg(util::Master, reply_to_master);
	}
	return reply_to_user;
}

string Feedback::FeedbackPrivate(const int64_t qq, const string msg)
{
	std::regex reg(kprivate_regex_);
	string reply_to_user, reply_to_master;
	if (std::regex_match(msg, feedback_match_, reg) == true)
	{
		reply_to_user = "已经告诉夜轮了，谢谢你的反馈（鞠躬）";
		reply_to_master = util::int64_ttos(qq) + ":\n" + feedback_match_.str(2);
		CQ::sendPrivateMsg(util::Master, reply_to_master);
	}
	return reply_to_user;
}
