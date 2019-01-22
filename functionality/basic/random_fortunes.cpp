#include "random_fortunes.h"
#include <cmath>
#include <ctime>
using namespace std::chrono;

Omikuji::Omikuji()
{
	origin_t_ = system_clock::to_time_t(system_clock::now());
}

std::string Omikuji::ShowHelpInfo(string msg)
{
	if (!msg.compare("help Omikuji") || !msg.compare("help 抽签"))
	{
		return string ("这是开发者留下的话：\n"
			"“抽签：可以抽一下你今天的音游运势。每天零点机绿会自行清空数据，所以每天都可以抽一次。\n"
			"群聊的语法为“@机绿 今日运势/抽签”，私聊就直接发送“今日运势/抽签”吧。繁体也是可以的。\n"
			"幸运程度从最好到最坏依次为大吉、中吉、小吉、吉、末吉、凶、大凶。"
			"这种东西，信则有，不信也罢。还是祝各位收割愉快（笑）”");
	}
	return "";
}

void Omikuji::GetDailyOmikuji(int64_t qq)
{
	string Omikuji;
	int Case;
	while (true)
	{
		Case = RandInt_binomial(3.0, 1.25, qq);
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

string Omikuji::ShowOmikujiPrivate(int64_t qq, string msg)
{
	string reply;
	if (msg == "抽签")
	{
		auto target_qq = daily_omikuji_.find(qq);
		//if user do not roll the Omikuji
		if (target_qq == daily_omikuji_.end())
		{
			GetDailyOmikuji(qq);
			reply = "今日音游运势：\n" + daily_omikuji_[qq];
		}
		else
		{
			reply = "你已经抽过今天的运势了……\n今日音游运势：\n" + target_qq->second;
		}
	}
	return reply;
}

string Omikuji::ShowOmikujiGroup(int64_t qq, string msg)
{
	string reply;
	std::regex reg(util::kat_beryl + "(今日运势|今日運勢|抽签|抽籤)");
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
	time_t now_t = system_clock::to_time_t(system_clock::now());
	tm *origin_tm = new tm(), *now_tm = new tm();
	localtime_s(origin_tm, &origin_t_);
	localtime_s(now_tm, &now_t);
	if (now_tm->tm_mday != origin_tm->tm_mday)
	{
		daily_omikuji_.clear();
		origin_t_ = now_t;
	}
}

string Omikuji::MasterCommand(int64_t group, int64_t qq, string msg)
{
	enum cmd { clear, view };
	std::map<string, int> cmd_stoi;
	cmd_stoi.insert({ "clear", clear });
	cmd_stoi.insert({ "view", view });

	if (qq == util::Master)
	{
		if (msg.compare("Omikuji all clear") == 0)
		{
			daily_omikuji_.clear();
			CQ::sendGroupMsg(group, "我已经往抽签筒里放了新的签了。夜轮放心，我摇得很均匀的！");
		}
		try {
			std::regex reg("(Omikuji )(.*)(\\[CQ:at,qq=)([1-9][0-9]{4,})(\\])(.)");
			std::smatch match;
			if (std::regex_match(msg, match, reg) == true)
			{
				int64_t target_qq = std::stoll(match.str(4));
				string cmd = match.str(2);
				switch (cmd_stoi[cmd])
				{
				case clear:
				{
					if (daily_omikuji_.find(target_qq) != daily_omikuji_.end())
					{
						daily_omikuji_.erase(target_qq);
						string reply = "好，清完啦！[CQ:at,qq=" + match.str(4) + "] 请再抽一次吧";
						CQ::sendGroupMsg(group, reply);
					}
					else
						CQ::sendGroupMsg(group, "夜轮你干啥啊？你指定的人没抽过签啊……");
				}
				break;
				case view:
				{
					if (daily_omikuji_.find(target_qq) != daily_omikuji_.end())
					{
						string reply = "你要看他的运势啊……\n" + daily_omikuji_[target_qq];
						CQ::sendGroupMsg(group, reply);
					}
					else
						CQ::sendGroupMsg(group, "夜轮你干啥啊？你指定的人没抽过签啊……");
				}
				break;
				default:
					break;
				}
			}
		} catch (std::regex_error e) {
			string error = e.what() + e.code();
			CQ::sendPrivateMsg(util::Master, error.c_str());
		}
		if (msg == "view time")
		{
			CQ::sendGroupMsg(group, std::to_string(origin_t_).c_str());
		}
	}
	return "";
}