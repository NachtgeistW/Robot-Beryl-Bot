#include "util/functionality.h"
#include "functionality/Admin_cmd.h"
using namespace std;
using namespace CQ;

//请加上static,表示这个logger只有本cpp有效
static Logger Robot_Beryl("Robot_Beryl");

//initialize
Feedback fb;
WholeRepeat wr;
Omikuji omi;
UrgeSleep us;
Heytea ht;


EVE_Enable(Enable)
{
	Robot_Beryl.Info("应用被启用");
	//load HEYTEA tea info
	ht.LoadTeaList(util::path + "heytea.txt");
	return 0;
}

EVE_PrivateMsg_EX(SendPrivateMsg)
{
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();
	auto message = eve.message;
	BlackCalculatePrivate bcp;

	if (!message.compare("help"))
		eve.sendMsg("这是开发者留下的话：\n"
			"“你好，这里夜轮。机绿目前支持的功能如下：\n"
			"反馈：语法为“@机绿 + 反馈/告诉你主人+（你想反馈给开发者的话）”，机绿会把这条消息转发给开发者。\n"
			"示例：@机绿 告诉你主人夏橙妹妹她错了\n"
			"抽签：可以抽一下你今天的音游运势。语法请发送“help Omikuji/抽签”。\n"
			"抽喜茶：喜茶了解一下？语法请发送“help heytea/喜茶”。"
			"算Cy1/2黑P：语法请发送“help 算黑P/p”。"
			"机绿的功能尚在不断完善中。如果出了什么意外的话请原谅。\n"
			"祝相处愉快（鞠躬）\n"
			"Creator: NachtgeistW. QQID: 562231326\n"
			"A botched imitation.”");

	//send feedback message
	msg << fb.FeedbackPrivate(eve.fromQQ, eve.message) << send;

	//Daily Omikuji. Functions are contained in random_fortunes.h and random_fortunes.cpp
	msg << omi.ShowHelpInfo(eve.message) << send;
	msg << omi.ShowOmikujiPrivate(eve.fromQQ, eve.message) << send;
	//omi.MasterCommand(eve.fromGroup, eve.fromQQ, eve.message);

	//HEYTEA. Functions are contained in random_heytea.h and random_heytea.cpp
	ht.ShowHelpInfo(eve.fromQQ, eve.message);
	ht.ShowTeaType(eve.fromQQ, eve.message);
	ht.ShowTea(eve.fromQQ, eve.message);

	bcp.Main(eve.fromQQ, eve.message);
	bcp.ShowHelpInfo(eve.fromQQ, eve.message);
}

EVE_GroupMsg_EX(GroupLightFunction) {
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();
	const int64_t group = eve.fromGroup;
	const int64_t qq = eve.fromQQ;

	std::regex help_reg(util::kat_beryl_regex + "help");
	if (std::regex_match(eve.message, help_reg))
	{
		eve.sendMsg( "这里机绿！是个bot，大概会帮你算算cytus黑P抽抽签之类的吧……可以私聊发个help看看！");
	}

	BlackCalculateGroup bcg;
	try {
		//send feedback message
		msg << fb.FeedbackGroup(eve.fromGroup, eve.fromQQ, eve.message) << send;

		//while only being at.
		At at;
		at.OnlyBeingAt(eve.fromGroup, eve.message);

		reply_origin_msg(eve.fromGroup, eve.fromQQ, eve.message);

		//Daily Omikuji. Functions are contained in random_fortunes.h and random_fortunes.cpp
		omi.ResetOmikuji();
		msg << omi.ShowHelpInfo(eve.message) << send;
		msg << omi.ShowOmikujiGroup(eve.fromQQ, eve.message) << send;
		omi.MasterCommand(eve.fromGroup, eve.fromQQ, eve.message);

		//HEYTEA. Functions are contained in random_heytea.h and random_heytea.cpp
		ht.ShowTea(eve.fromGroup, eve.fromQQ, eve.message);

		bcg.Main(group, qq, eve.message);
	}
	catch (std::runtime_error err) {
		std::string to_be_sent = "我很确定，出现runtime_error了。\n"
			"消息是从群" + util::int64_ttos(eve.fromGroup) + "里的成员" + util::int64_ttos(eve.fromQQ) + "发送的“" + eve.message + "”。\n"
			"出错的模块是GroupLightFunction。原因是" + err.what() + "\n"
			"对不起……请帮忙看一下。";
		sendPrivateMsg(util::Master, to_be_sent);
	}
	catch (...) {
		std::string to_be_sent = "好、好像出问题了！\n"
			"消息是从群" + util::int64_ttos(eve.fromGroup) + "里的成员" + util::int64_ttos(eve.fromQQ) + "发送的“" + eve.message + "”。\n"
			"出错的模块是GroupLightFunction。\n"
			"真的很对不起，请帮忙看一下！";
		sendPrivateMsg(util::Master, to_be_sent);
	}

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
