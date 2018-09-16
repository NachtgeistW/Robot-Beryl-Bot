#include "util/functionality.h"
using namespace std;
using namespace CQ;

//请加上static,表示这个logger只有本cpp有效
static Logger Robot_Beryl("Robot_Beryl");

//initialize
feedback fb;
WholeRepeat wr;

EVE_PrivateMsg_EX(SendPrivateMsg)
{
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();
	auto message = eve.message;

	if (!message.compare("test"))
		msg << "已启动" << send;

	if (!message.compare("help"))
		eve.sendMsg("你好，这里是机器人小绿。机绿目前支持的功能如下：\n"
		"反馈：语法为“艾特机器人 + 反馈/告诉你主人 + （你想反馈给开发者的话）”，机绿会把这条消息转发给开发者。\n"
		"示例：@机绿 告诉你主人夏橙妹妹她错了\n"
		"另有一些算不上功能的属性，如嘲讽。\n"
		"机绿的功能尚在不断完善中。如果出了什么意外的话请原谅。\n"
		"祝使用愉快（鞠躬）\n"
		"Creator: NachtgeistW. QQID:562231326\n"
		"A botched imitation.");

	//send feedback message
	msg << fb.fb_in_privt(eve.fromQQ, eve.message) << send;
}

EVE_GroupMsg_EX(GroupLightFunction) {
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();

	//send feedback message
	msg << fb.fb_in_group(eve.fromGroup, eve.fromQQ, eve.message) << send;

	/*while only being at.
	There is a problem that I can't use compare and I am forced to use find,
	so Robot Beryl will also respone when text following the at.*/
	At at;
	at.only_being_at(eve.fromGroup, eve.message);

	if (eve.message.find("♂") != string::npos && !util::checkBot(eve.fromQQ, util::Robot))
		msg << code::at(eve.fromQQ) << " 这是什么奇怪符号？" << send;

}

EVE_GroupMsg_EX(SetGroupBan){
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;

	auto msg = eve.sendMsg();
	auto message = eve.message;
	GroupMemberInfo HikariInfo = getGroupMemberInfo(eve.fromGroup, getLoginQQ(), true),
		MemberAInfo = getGroupMemberInfo(eve.fromGroup, eve.fromQQ, true);
	const int HikariPermission = HikariInfo.permissions, MemberAPermission = MemberAInfo.permissions;

	//use command to set whole group ban
	if (message.find("全员禁言") == 0 || message.find("全员烟") == 0 || message.find("碹镑铱鸹") == 0)
	{
		if (MemberAPermission >= 2)
		{
			if (HikariPermission == 2 || HikariPermission == 3)
			{
				eve.setGroupWholeBan(true);
				msg << "９芾碓薄 Hikari ？僚袅巳浛苯耝浴" << send;
			}
			else
				msg << "我做不到……" << send;
		}
		else
			msg << code::at(eve.fromQQ) << " 你不是群主或管理，你碹没用呢……" << send;
	}
	if (message.find("全员戒烟") == 0 && HikariPermission >= 2)
	{
		eve.setGroupWholeBan(false);
		msg << "９芾碓薄 Hikari ９乇樟巳浛苯耝浴" << send;
	}
	
	//use command to ban a single group member
	if (message.find("给") == 0 && (message.rfind("上") != string::npos 
		//|| (message.rfind("递烟") != string::npos)
		))
	{
		if (HikariPermission >= 2)
		{
			vector<int64_t>banid;
			getBanID(eve.message, banid); 

			for (auto begin = banid.begin(); begin != banid.end(); begin++)
			{
				//A是烟人的，B是被烟的
				GroupMemberInfo MemberBInfo = getGroupMemberInfo(eve.fromGroup, *begin, true);
				const int MemberBPermission = MemberBInfo.permissions;
				if (message.find("烟上") != string::npos || message.find("上烟") != string::npos || message.find("递烟") != string::npos)
					useCmdtoBan(eve, MemberAInfo, MemberBInfo, 10 * 60);
				if (message.find("上中华") != string::npos)
					useCmdtoBan(eve, MemberAInfo, MemberBInfo, 30 * 60);
				if (message.find("上大中华") != string::npos)
					useCmdtoBan(eve, MemberAInfo, MemberBInfo, 60 * 60 * 2);
			}
		}
		else
			msg << "我做不到……" << send;
	}
	if (message.find("给") == 0 && message.rfind("戒烟") != string::npos)
	{
		if (HikariPermission >= 2)
		{
			vector<int64_t>banid;
			getBanID(eve.message, banid);
			for (auto begin = banid.begin(); begin != banid.end(); begin++)
				setGroupBan(eve.fromGroup, *begin, 0);
			msg << "怎么样，还想再来一次吗？（笑）" << send;
		}
		else
			msg << "我做不到……" << send;
	}
}

EVE_GroupMsg_EX(Repeat_Taunt) {
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();
	
	//functions are contained in rage.h and rage.cpp
	try {
		msg << wr.stopWholeRepeat(eve.fromGroup, eve.message) << send;
		//msg << tauntProUp(eve.fromGroup, eve.fromQQ, eve.message) << send;
	}
	catch (...) {
		std::string to_be_sent = "好、好像出问题了！\n"
			"消息是从群" + util::int64_ttos(eve.fromGroup) + "里的成员" + util::int64_ttos(eve.fromQQ) + "发送的“" + eve.message + "”。\n"
			"出错的模块是Repeat_Taunt。\n"
			"真的很对不起，请帮忙看一下！";
		sendPrivateMsg(util::Master, to_be_sent);
	}
}
