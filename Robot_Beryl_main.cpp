#include "util/functionality.h"
#include "functionality/Admin_cmd.h"
using namespace std;
using namespace CQ;

//�����static,��ʾ���loggerֻ�б�cpp��Ч
static Logger Robot_Beryl("Robot_Beryl");

//initialize
Feedback fb;
WholeRepeat wr;
Omikuji omi;
UrgeSleep us;
Heytea ht;

EVE_Enable(Enable)
{
	Robot_Beryl.Info("Ӧ�ñ�����");
	//load HEYTEA tea info
	ht.LoadTeaList(util::path + "heytea.txt");

	return 0;
}
EVE_PrivateMsg_EX(SendPrivateMsg)
{
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();
	auto message = eve.message;

	if (!message.compare("test"))
		msg << "������" << send;
	if (!message.compare("help"))
		eve.sendMsg("���ǿ��������µĻ���\n"
			"����ã�����ҹ�֡�����Ŀǰ֧�ֵĹ������£�\n"
			"�������﷨Ϊ��@���� + ����/���������� + �����뷴���������ߵĻ����������̻��������Ϣת���������ߡ�\n"
			"ʾ����@���� �����������ĳ�����������\n"
			"��ǩ�����Գ�һ���������������ơ������﷨�뷢�͡�help Omikuji��help ��ǩ���鿴��\n"
			"��ϲ�裺ϲ���˽�һ�£������﷨�뷢�͡�help heytea��help ϲ�衱�鿴��"
			"���̵Ĺ������ڲ��������С��������ʲô����Ļ���ԭ�¡�\n"
			"ף�ദ��죨�Ϲ���\n"
			"Creator: NachtgeistW. QQID: 562231326\n"
			"A botched imitation.��");

	//send feedback message
	msg << fb.FbInPrivt(eve.fromQQ, eve.message) << send;

	//Daily Omikuji. Functions are contained in random_fortunes.h and random_fortunes.cpp
	msg << omi.ShowHelpInfo(eve.message) << send;
	msg << omi.ShowOmikujiPrivate(eve.fromQQ, eve.message) << send;
	//omi.MasterCommand(eve.fromGroup, eve.fromQQ, eve.message);

	//HEYTEA. Functions are contained in random_heytea.h and random_heytea.cpp
	ht.ShowHelpInfo(eve.fromQQ, eve.message);
	ht.ShowTeaType(eve.fromQQ, eve.message);
	ht.ShowTea(eve.fromQQ, eve.message);
}

EVE_GroupMsg_EX(GroupLightFunction) {
	Robot_Beryl.Debug() << DEBUGINFO << eve.message;
	auto msg = eve.sendMsg();
	int64_t group = eve.fromGroup;
	int64_t qq = eve.fromQQ;

	try {
		//send feedback message
		msg << fb.fb_in_group(eve.fromGroup, eve.fromQQ, eve.message) << send;

		//while only being at.
		At at;
		at.only_being_at(eve.fromGroup, eve.message);

		reply_origin_msg(eve.fromGroup, eve.fromQQ, eve.message);

		//Daily Omikuji. Functions are contained in random_fortunes.h and random_fortunes.cpp
		msg << omi.ShowHelpInfo(eve.message) << send;
		msg << omi.ShowOmikujiGroup(eve.fromQQ, eve.message) << send;
		omi.ResetOmikuji();
		omi.MasterCommand(eve.fromGroup, eve.fromQQ, eve.message);

		//HEYTEA. Functions are contained in random_heytea.h and random_heytea.cpp
		ht.ShowTea(eve.fromGroup, eve.fromQQ, eve.message);
	}
	catch (std::runtime_error err) {
		std::string to_be_sent = "�Һ�ȷ��������runtime_error�ˡ�\n"
			"��Ϣ�Ǵ�Ⱥ" + util::int64_ttos(eve.fromGroup) + "��ĳ�Ա" + util::int64_ttos(eve.fromQQ) + "���͵ġ�" + eve.message + "����\n"
			"�����ģ����GroupLightFunction��ԭ����" + err.what() + "\n"
			"�Բ��𡭡����æ��һ�¡�";
		sendPrivateMsg(util::Master, to_be_sent);
	}
	catch (...) {
		std::string to_be_sent = "�á�����������ˣ�\n"
			"��Ϣ�Ǵ�Ⱥ" + util::int64_ttos(eve.fromGroup) + "��ĳ�Ա" + util::int64_ttos(eve.fromQQ) + "���͵ġ�" + eve.message + "����\n"
			"�����ģ����GroupLightFunction��\n"
			"��ĺܶԲ������æ��һ�£�";
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
