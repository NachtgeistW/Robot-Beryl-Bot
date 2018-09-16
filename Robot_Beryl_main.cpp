#include "util/functionality.h"
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
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
		msg << "������" << send;

	if (!message.compare("help"))
		eve.sendMsg("��ã������ǻ�����С�̡�����Ŀǰ֧�ֵĹ������£�\n"
		"�������﷨Ϊ�����ػ����� + ����/���������� + �����뷴���������ߵĻ����������̻��������Ϣת���������ߡ�\n"
		"ʾ����@���� �����������ĳ�����������\n"
		"����һЩ�㲻�Ϲ��ܵ����ԣ��糰��\n"
		"���̵Ĺ������ڲ��������С��������ʲô����Ļ���ԭ�¡�\n"
		"ףʹ����죨�Ϲ���\n"
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

	if (eve.message.find("��") != string::npos && !util::checkBot(eve.fromQQ, util::Robot))
		msg << code::at(eve.fromQQ) << " ����ʲô��ַ��ţ�" << send;

}

EVE_GroupMsg_EX(SetGroupBan){
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;

	auto msg = eve.sendMsg();
	auto message = eve.message;
	GroupMemberInfo HikariInfo = getGroupMemberInfo(eve.fromGroup, getLoginQQ(), true),
		MemberAInfo = getGroupMemberInfo(eve.fromGroup, eve.fromQQ, true);
	const int HikariPermission = HikariInfo.permissions, MemberAPermission = MemberAInfo.permissions;

	//use command to set whole group ban
	if (message.find("ȫԱ����") == 0 || message.find("ȫԱ��") == 0 || message.find("�۰�ҿ�") == 0)
	{
		if (MemberAPermission >= 2)
		{
			if (HikariPermission == 2 || HikariPermission == 3)
			{
				eve.setGroupWholeBan(true);
				msg << "�����Ա� Hikari �������ț����^ԡ" << send;
			}
			else
				msg << "������������" << send;
		}
		else
			msg << code::at(eve.fromQQ) << " �㲻��Ⱥ�����������û���ء���" << send;
	}
	if (message.find("ȫԱ����") == 0 && HikariPermission >= 2)
	{
		eve.setGroupWholeBan(false);
		msg << "�����Ա� Hikari ��ر���ț����^ԡ" << send;
	}
	
	//use command to ban a single group member
	if (message.find("��") == 0 && (message.rfind("��") != string::npos 
		//|| (message.rfind("����") != string::npos)
		))
	{
		if (HikariPermission >= 2)
		{
			vector<int64_t>banid;
			getBanID(eve.message, banid); 

			for (auto begin = banid.begin(); begin != banid.end(); begin++)
			{
				//A�����˵ģ�B�Ǳ��̵�
				GroupMemberInfo MemberBInfo = getGroupMemberInfo(eve.fromGroup, *begin, true);
				const int MemberBPermission = MemberBInfo.permissions;
				if (message.find("����") != string::npos || message.find("����") != string::npos || message.find("����") != string::npos)
					useCmdtoBan(eve, MemberAInfo, MemberBInfo, 10 * 60);
				if (message.find("���л�") != string::npos)
					useCmdtoBan(eve, MemberAInfo, MemberBInfo, 30 * 60);
				if (message.find("�ϴ��л�") != string::npos)
					useCmdtoBan(eve, MemberAInfo, MemberBInfo, 60 * 60 * 2);
			}
		}
		else
			msg << "������������" << send;
	}
	if (message.find("��") == 0 && message.rfind("����") != string::npos)
	{
		if (HikariPermission >= 2)
		{
			vector<int64_t>banid;
			getBanID(eve.message, banid);
			for (auto begin = banid.begin(); begin != banid.end(); begin++)
				setGroupBan(eve.fromGroup, *begin, 0);
			msg << "��ô������������һ���𣿣�Ц��" << send;
		}
		else
			msg << "������������" << send;
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
		std::string to_be_sent = "�á�����������ˣ�\n"
			"��Ϣ�Ǵ�Ⱥ" + util::int64_ttos(eve.fromGroup) + "��ĳ�Ա" + util::int64_ttos(eve.fromQQ) + "���͵ġ�" + eve.message + "����\n"
			"�����ģ����Repeat_Taunt��\n"
			"��ĺܶԲ������æ��һ�£�";
		sendPrivateMsg(util::Master, to_be_sent);
	}
}
