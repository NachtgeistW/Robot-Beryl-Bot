#include "random_fortunes.h"
#include <cmath>

void Omikuji::GetDailyOmikuji(int64_t qq)
{
	string Omikuji;
	int Case;
	while (1)
	{
		Case = RandInt_binomial(3.0, 1.25, qq);
		if (Case >= 0 && Case <= 7)
			break;
	}
	//select an Omikuji
	switch (Case)
	{
	case 0:
		Omikuji = "�� / Great Blessing";
		break;
	case 1:
		Omikuji = "�м� / Middle Blessing";
		break;
	case 2:
		Omikuji = "С�� / Small Blessing";
		break;
	case 3:
		Omikuji = "�� / Blessing";
		break;
	case 4:
		Omikuji = "ĩ�� / Ending Blessing";
		break;
	case 5:
		Omikuji = "�� / Curse";
		break;
	case 6:
		Omikuji = "����  / Great Curse";
		break;
	default:
		Omikuji = "Error";
		break;
	}
	
	//push back
	daily_omikuji_.insert(std::make_pair(qq, Omikuji));
}

void Omikuji::ShowDailyOmikuji(int64_t group, int64_t qq, string msg)
{
	std::regex reg(command);
	if (std::regex_match(msg, reg) == true)
	{
		auto target_qq = daily_omikuji_.find(qq);
		string reply;
		//if user do not roll the Omikuji
		if (target_qq == daily_omikuji_.end())
		{
			GetDailyOmikuji(qq);
			reply = "[CQ:at,qq=" + util::int64_ttos(qq) + "] \n�����������ƣ�\n" + daily_omikuji_[qq];
		}
		else
		{
			reply = "[CQ:at,qq=" + util::int64_ttos(qq) + "] ���Ѿ��������������ˡ���\n�����������ƣ�\n" + target_qq->second;
		}
		CQ::sendGroupMsg(group, reply);
	}
}

void Omikuji::ResetOmikuji(int64_t qq, string msg)
{
	if (qq == util::Master && msg.compare("clear") == 0)
	{
		daily_omikuji_.clear();
		CQ::sendPrivateMsg(util::Master, "���Ѿ�����ǩͲ������µ�ǩ�ˡ�ҹ�ַ��ģ���ҡ�úܾ��ȵģ�");
	}
}
