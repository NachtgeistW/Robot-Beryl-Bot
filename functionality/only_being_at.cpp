#include "only_being_at.h"

string At::select_reply(void)
{
	string reply_to_member;
	switch (util::RandInt_uniform(0, 45))
	{
	case 0:
		reply_to_member = "夜轮？就是那个又菜又有重度拖延症还整天咕咕咕的人吗？";
		break;
	case 1:		case 2:		case 3:		case 4:		case 5:
		reply_to_member = "你好:D";
		break;
	case 6:		case 7:		case 8:		case 9:		case 10:
		reply_to_member = "做人真难";
		break;
	case 11:	case 12:	case 13:	case 14:	case 15:
		reply_to_member = "http://nachtgeistw.cn/";
		break;
	case 16:	case 17:	case 18:	case 19:	case 20:
		reply_to_member = "小声说一句，我说的人话肯定不是我说的";
		break;
	case 21:	case 22:	case 23:	case 24:	case 25:
		reply_to_member = "抱歉，我不是聊天机器人啦……唔，暂时不是";
		break;
	case 26:	case 27:	case 28:	case 29:	case 30:
		reply_to_member = "你找我有事吗？";
		break;
	case 31:	case 32:	case 33:	case 34:	case 35:
		reply_to_member = "黑白棋，对吗？黑白棋的话艾特万寿菊问问？対立和猫也是个不错的对手";
		break;
	case 36:	case 37:	case 38:	case 39:	case 40:
		reply_to_member = "你想玩UNO？UNO的话请找那个撑阳伞的小姐姐";
		break;
	case 41:	case 42:	case 43:	case 44:	case 45:
		reply_to_member = "来D.N.ChessRoom（674525758）玩吗？UNO、黑白棋、数独和或帝灭斗井字棋了解一下？";
		break;
	case 46:	case 47:	case 48:	case 49:	case 50:
		reply_to_member = "来杯喜茶的芝士夜轮，啊不对，芝士绿妍吗？（日常安利）";
		break;
	default:
		reply_to_member = "目标是以科学的力量凌驾于超能力之上！为了伯伦希尔的荣耀！";
		//reply_to_member = "其实夜轮有时候会很自卑的。如果可以的话，请安慰一下她吧。";
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
