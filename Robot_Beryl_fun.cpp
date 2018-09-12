#include <string>
#include <regex>

#include "util/functionality.h"

using namespace std;
using namespace CQ;

const char *onlyBeingAt(void)
{
	switch (util::randNum(40))
	{
	case 0:
		return "夜轮？就是那个又菜又有重度拖延症还整天咕咕咕的人吗？";
		break;
	case 1:		case 2:		case 3:		case 4:		case 5:
		return "你好:D";
		break;
	case 6:		case 7:		case 8:		case 9:		case 10:
		return "做人真难";
		break;
	case 11:	case 12:	case 13:	case 14:	case 15:
		return "http://nachtgeistw.cn/";
		break;
	case 16:	case 17:	case 18:	case 19:	case 20:
		return "小声说一句，我说的人话肯定不是我说的";
		break;
	case 21:	case 22:	case 23:	case 24:	case 25:
		return "抱歉，我不是聊天机器人啦……唔，暂时不是";
		break;
	case 26:	case 27:	case 28:	case 29:	case 30:
		return "你找我有事吗？";
		break;
	case 31:	case 32:	case 33:	case 34:	case 35:
		return "黑白棋，对吗？黑白棋的话艾特万寿菊问问？対立和猫也是个不错的对手。";
		break;
	case 36:	case 37:	case 38:	case 39:	case 40:
		return "你想玩UNO？UNO的话请找対立";
		break;
	default:
		return "其实夜轮有时候会很自卑的。如果可以的话，请安慰一下她吧。";
		break;
	}
}

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