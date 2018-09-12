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
		return "ҹ�֣������Ǹ��ֲ������ض�����֢�����칾����������";
		break;
	case 1:		case 2:		case 3:		case 4:		case 5:
		return "���:D";
		break;
	case 6:		case 7:		case 8:		case 9:		case 10:
		return "��������";
		break;
	case 11:	case 12:	case 13:	case 14:	case 15:
		return "http://nachtgeistw.cn/";
		break;
	case 16:	case 17:	case 18:	case 19:	case 20:
		return "С��˵һ�䣬��˵���˻��϶�������˵��";
		break;
	case 21:	case 22:	case 23:	case 24:	case 25:
		return "��Ǹ���Ҳ����������������������ʱ����";
		break;
	case 26:	case 27:	case 28:	case 29:	case 30:
		return "������������";
		break;
	case 31:	case 32:	case 33:	case 34:	case 35:
		return "�ڰ��壬���𣿺ڰ���Ļ��������پ����ʣ�������èҲ�Ǹ�����Ķ��֡�";
		break;
	case 36:	case 37:	case 38:	case 39:	case 40:
		return "������UNO��UNO�Ļ����Ҍ���";
		break;
	default:
		return "��ʵҹ����ʱ�����Ա��ġ�������ԵĻ����밲οһ�����ɡ�";
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
		msg << "�Ҳ����̵�" << send;
	else if (MemberBInfo.QQID == util::Master)
		msg << "�ҡ������������˼����������������������Բ��𡭡�" << send;
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
		msg << "���Ƕ���Ҳ�ǹ�����������������" << send;
	else
		msg << "����" << send;
}


/*void throwError(static runtime_error err)
{
	sendPrivateMsg(Master, "���֣����õļ�������ˡ������ľ����ǡ���");
	sendPrivateMsg(Master, err.what());
}
*/