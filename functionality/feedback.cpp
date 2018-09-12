//test
#include "feedback.h"

inline string feedback::fb_in_group(int64_t groupID, int64_t qq, string msg)
{
	string reply_to_user, reply_to_master;
	if (std::regex_match(msg, match, group))
	{
		reply_to_user = CQ::code::at(qq) + "�Ѿ�����ҹ���ˣ�лл��ķ������Ϲ���";
		reply_to_master = "The feedback from member " + util::int64_ttos(qq)
			+ "in Group" + util::int64_ttos(groupID) + ":\n" + msg;
		CQ::sendPrivateMsg(util::Master, reply_to_master);
	}
	return reply_to_user;
}

inline string feedback::fb_in_privt(int64_t qq, string msg)
{
	string reply_to_user, reply_to_master;
	if (std::regex_match(msg, match, privt))
	{
		reply_to_user = "�Ѿ�����ҹ���ˣ�лл��ķ������Ϲ���";
		reply_to_master = "The feedback from user " + util::int64_ttos(qq) + ":\n" + msg;
		CQ::sendPrivateMsg(util::Master, reply_to_master);
	}
	return reply_to_user;
}
