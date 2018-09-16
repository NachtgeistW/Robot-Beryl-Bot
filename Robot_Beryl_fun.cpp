#include <string>
#include <regex>

#include "util/functionality.h"

using namespace std;
using namespace CQ;

void getBanID(const string message, vector<int64_t> &banid)
{
	regex r("\\d+"); //match all the QQID
	for (sregex_iterator it(message.begin(), message.end(), r), end_it; it != end_it; ++it)
		banid.push_back(stoll(it->str()));
}

void useCmdtoBan(EVEGroupMsg &eve, GroupMemberInfo MemberAInfo, GroupMemberInfo MemberBInfo, int64_t time)
{
	auto msg = eve.sendMsg();
	if (MemberBInfo.QQID == util::Beryl)
		msg << "我不抽烟的" << send;
	else if (MemberBInfo.QQID == util::Master)
		msg << "我……明白你的意思……但我真的做不到……对不起……" << send;
	else if (MemberAInfo.permissions == 1 && MemberBInfo.permissions == 1)
	{
		if (util::randNum(15) == 15)
			setGroupBan(eve.fromGroup, MemberAInfo.QQID, time);
		else
			setGroupBan(eve.fromGroup, MemberBInfo.QQID, time);
	}
	else if (MemberAInfo.permissions == 1 && MemberBInfo.permissions >= 2)
	{
		setGroupBan(eve.fromGroup, MemberAInfo.QQID, time);
		msg << "Result: Clear" << send;
	}
	else if (MemberAInfo.permissions >= 2 && MemberBInfo.permissions == 1)
	{
		setGroupBan(eve.fromGroup, MemberBInfo.QQID, time);
		msg << "Result: Clear" << send;
	}
	else if (MemberAInfo.permissions >= 2 && MemberBInfo.permissions >= 2)
		msg << "可是对面也是管理啊，我做不到……" << send;
	else
		msg << "……" << send;
}


/*void throwError(static runtime_error err)
{
	sendPrivateMsg(Master, "啊咧，美好的记忆崩塌了……最后的景象是……");
	sendPrivateMsg(Master, err.what());
}
*/