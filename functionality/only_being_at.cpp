#include "only_being_at.h"

string At::select_reply(void)
{
	string reply_to_member;
	switch (util::RandInt_uniform(0, 45))
	{
	case 0:
		reply_to_member = "ҹ�֣������Ǹ��ֲ������ض�����֢�����칾����������";
		break;
	case 1:		case 2:		case 3:		case 4:		case 5:
		reply_to_member = "���:D";
		break;
	case 6:		case 7:		case 8:		case 9:		case 10:
		reply_to_member = "��������";
		break;
	case 11:	case 12:	case 13:	case 14:	case 15:
		reply_to_member = "http://nachtgeistw.cn/";
		break;
	case 16:	case 17:	case 18:	case 19:	case 20:
		reply_to_member = "С��˵һ�䣬��˵���˻��϶�������˵��";
		break;
	case 21:	case 22:	case 23:	case 24:	case 25:
		reply_to_member = "��Ǹ���Ҳ����������������������ʱ����";
		break;
	case 26:	case 27:	case 28:	case 29:	case 30:
		reply_to_member = "������������";
		break;
	case 31:	case 32:	case 33:	case 34:	case 35:
		reply_to_member = "�ڰ��壬���𣿺ڰ���Ļ��������پ����ʣ�������èҲ�Ǹ�����Ķ���";
		break;
	case 36:	case 37:	case 38:	case 39:	case 40:
		reply_to_member = "������UNO��UNO�Ļ������Ǹ�����ɡ��С���";
		break;
	case 41:	case 42:	case 43:	case 44:	case 45:
		reply_to_member = "��D.N.ChessRoom��674525758������UNO���ڰ��塢�����ͻ���𶷾������˽�һ�£�";
		break;
	case 46:	case 47:	case 48:	case 49:	case 50:
		reply_to_member = "����ϲ���֥ʿҹ�֣������ԣ�֥ʿ�����𣿣��ճ�������";
		break;
	default:
		reply_to_member = "Ŀ�����Կ�ѧ����������ڳ�����֮�ϣ�Ϊ�˲���ϣ������ҫ��";
		//reply_to_member = "��ʵҹ����ʱ�����Ա��ġ�������ԵĻ����밲οһ�����ɡ�";
		break;
	}
	return reply_to_member;
}

void At::only_being_at(int64_t group, string msg)
{
	std::regex reg(at);
	string reply = select_reply();
	if (std::regex_match(msg, reg))
		CQ::sendGroupMsg(group, reply);
}
