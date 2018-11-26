#include "random_fortunes.h"
#include <cmath>
#include <chrono>

string Omikuji::ShowHelpInfo(string msg)
{
	if (!msg.compare("help Omikuji") || !msg.compare("help 抽签"))
	{
		return string ("这是开发者留下的话：\n"
			"“抽签：可以抽一下你今天的音游运势。每天零点机绿会自行清空数据，所以每天都可以抽一次。\n"
			"语法为“@机绿 今日运势/抽签”。繁体也是可以的。\n"
			"幸运程度从最好到最坏依次为大吉、中吉、小吉、吉、末吉、凶、大凶。"
			"吉嘛大概就是不好也不坏。"
			"这种东西，信则有，不信也罢。还是祝各位收割愉快（笑）”");
	}
	return "";
}

void Omikuji::GetDailyOmikuji(int64_t qq)
{
	string Omikuji;
	int Case;
	while (1)
	{
		Case = RandInt_binomial(3.0, 1.25);
		if (Case >= 0 && Case <= 7)
			break;
	}
	//select an Omikuji
	switch (Case)
	{
	case 0:
		Omikuji = "大吉 / Great Blessing\n（*゜ー゜*）？\n你今天什么也别做了快去收歌吧！";
		break;
	case 1:
		Omikuji = "中吉 / Middle Blessing\n我猜你今天打歌的话，一定会有好结果的吧:-D";
		break;
	case 2:
		Omikuji = "小吉 / Small Blessing\n大概今天会有意外的惊喜？";
		break;
	case 3:
		Omikuji = "吉 / Blessing\n不好也不坏呢";
		break;
	case 4:
		Omikuji = "末吉 / Ending Blessing\n今天应该不是你收歌的好时间，但是你可以试试(￣▽￣)\"";
		break;
	case 5:
		Omikuji = "凶 / Curse\n签上说今天不宜打歌>.<";
		break;
	case 6:
		Omikuji = "大凶  / Great Curse\n……确认了一下是大凶……要不你今天去做别的事情吧";
		break;
	default:
		Omikuji = "Error";
		break;
	}
	
	//push back
	daily_omikuji_.insert(std::make_pair(qq, Omikuji));
}

string Omikuji::ShowDailyOmikuji(int64_t qq, string msg)
{
	string reply;
	std::regex reg("(今日运势|今日運勢|抽签|抽籤)(\\[CQ:at,qq=)?(" + std::to_string(util::Beryl) + ")?(\\])?(.*)?");
	if (std::regex_match(msg, reg) == true)
	{
		auto target_qq = daily_omikuji_.find(qq);
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
	}
	return reply;
}

void Omikuji::ResetOmikuji(void)
{
	//auto clear
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
}

string Omikuji::MasterCommand(int64_t qq, string msg)
{
	if (qq == util::Master)
	{
		if (msg.compare("Omikuji all clear") == 0)
		{
			daily_omikuji_.clear();
			return "我已经往抽签筒里放了新的签了。夜轮放心，我摇得很均匀的！";
		}
		try {
			std::regex reg("(Omikuji clear)(\\[CQ:at,qq=)([1-9][0-9]{4,})(\\])(.*)");
			std::smatch match;
			if (std::regex_match(msg, match, reg) == true)
			{
				int64_t target_qq = std::stoll(match.str(3));
				if (daily_omikuji_.find(target_qq) != daily_omikuji_.end())
				{
					daily_omikuji_.erase(target_qq);
					return string("好，清完啦！[CQ:at,qq=" + match.str(3) + "] 请再抽一次吧");
				}
				else
					return "夜轮你干啥啊？你指定的人没抽过签啊……";
			}
		} catch (std::regex_error e) {
			string error = e.what() + e.code();
			CQ::sendPrivateMsg(util::Master, error.c_str());
		}
	}
	return "";
}