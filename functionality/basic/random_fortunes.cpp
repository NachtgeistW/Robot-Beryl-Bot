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
		Omikuji = "大吉 / Great Blessing";
		break;
	case 1:
		Omikuji = "中吉 / Middle Blessing";
		break;
	case 2:
		Omikuji = "小吉 / Small Blessing";
		break;
	case 3:
		Omikuji = "吉 / Blessing";
		break;
	case 4:
		Omikuji = "末吉 / Ending Blessing";
		break;
	case 5:
		Omikuji = "凶 / Curse";
		break;
	case 6:
		Omikuji = "大凶  / Great Curse";
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
			reply = "[CQ:at,qq=" + util::int64_ttos(qq) + "] \n今日音游运势：\n" + daily_omikuji_[qq];
		}
		else
		{
			reply = "[CQ:at,qq=" + util::int64_ttos(qq) + "] 你已经抽过今天的运势了……\n今日音游运势：\n" + target_qq->second;
		}
		CQ::sendGroupMsg(group, reply);
	}
}

void Omikuji::ResetOmikuji(int64_t qq, string msg)
{
	if (qq == util::Master && msg.compare("clear") == 0)
	{
		daily_omikuji_.clear();
		CQ::sendPrivateMsg(util::Master, "我已经往抽签筒里放了新的签了。夜轮放心，我摇得很均匀的！");
	}
}
