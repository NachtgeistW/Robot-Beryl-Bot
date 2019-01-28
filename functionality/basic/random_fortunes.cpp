#include "random_fortunes.h"
#include <cmath>
#include <ctime>
using namespace std::chrono;

Omikuji::Omikuji()
{
	origin_t_ = system_clock::to_time_t(system_clock::now());
}

std::string Omikuji::ShowHelpInfo(const string msg)
{
	if (!msg.compare("help Omikuji") || !msg.compare("help ��ǩ"))
	{
		return string ("���ǿ��������µĻ���\n"
			"����ǩ�����Գ�һ���������������ơ�ÿ�������̻�����������ݣ�����ÿ�춼���Գ�һ�Ρ�\n"
			"Ⱥ�ĵ��﷨Ϊ��@���� ��������/��ǩ����˽�ľ�ֱ�ӷ��͡���������/��ǩ���ɡ�����Ҳ�ǿ��Եġ�\n"
			"���˳̶ȴ���õ������Ϊ�󼪡��м���С��������ĩ�����ס����ס�"
			"���ֶ����������У�����Ҳ�ա�����ף��λ�ո���죨Ц����");
	}
	return "";
}

void Omikuji::GetDailyOmikuji(const int64_t qq)
{
	string omikuji;
	int Case;
	while (true)
	{
		Case = RandIntBinomial(3.0, 1.25, qq);
		if (Case >= 0 && Case <= 6)
			break;
	}
	//select an Omikuji
	switch (Case)
	{
	case 0:
		omikuji = "�� / Great Blessing\n��*�b�`�b*����\n�����ʲôҲ�����˿�ȥ�ո�ɣ�";
		break;
	case 1:
		omikuji = "�м� / Middle Blessing\n�Ҳ��������Ļ���һ�����кý���İ�:-D";
		break;
	case 2:
		omikuji = "С�� / Small Blessing\n��Ž����������ľ�ϲ��";
		break;
	case 3:
		omikuji = "�� / Blessing\n����Ҳ������";
		break;
	case 4:
		omikuji = "ĩ�� / Ending Blessing\n����Ӧ�ò������ո�ĺ�ʱ�䣬�������������(������)\"";
		break;
	case 5:
		omikuji = "�� / Curse\nǩ��˵���첻�˴��>.<";
		break;
	case 6:
		omikuji = "����  / Great Curse\n����ȷ����һ���Ǵ��ס���Ҫ�������ȥ����������";
		break;
	default:
		omikuji = "Error";
		break;
	}
	
	//push back
	daily_omikuji_.insert(std::make_pair(qq, omikuji));
}

string Omikuji::ShowOmikujiPrivate(const int64_t qq, const string msg)
{
	string reply;
	if (msg == "��ǩ")
	{
		auto target_qq = daily_omikuji_.find(qq);
		//if user do not roll the Omikuji
		if (target_qq == daily_omikuji_.end())
		{
			GetDailyOmikuji(qq);
			reply = "�����������ƣ�\n" + daily_omikuji_[qq];
		}
		else
		{
			reply = "���Ѿ��������������ˡ���\n�����������ƣ�\n" + target_qq->second;
		}
	}
	return reply;
}

string Omikuji::ShowOmikujiGroup(const int64_t qq, const string msg)
{
	string reply;
	std::regex reg(util::kat_beryl_regex + "(��������|�����\��|��ǩ|��`)");
	if (std::regex_match(msg, reg) == true)
	{
		auto target_qq = daily_omikuji_.find(qq);
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

string Omikuji::MasterCommand(const int64_t group, const int64_t qq, const string msg)
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
			CQ::sendGroupMsg(group, "���Ѿ�����ǩͲ������µ�ǩ�ˡ�ҹ�ַ��ģ���ҡ�úܾ��ȵģ�");
		}
		try {
			std::regex reg("sudo Omikuji (.*)\\[CQ:at,qq=([1-9][0-9]{4,})\\].");
			std::smatch match;
			if (std::regex_match(msg, match, reg) == true)
			{
				int64_t target_qq = std::stoll(match.str(2));
				string cmd = match.str(1);
				switch (cmd_stoi[cmd])
				{
				case clear:
				{
					if (daily_omikuji_.find(target_qq) != daily_omikuji_.end())
					{
						daily_omikuji_.erase(target_qq);
						string reply = "�ã���������[CQ:at,qq=" + match.str(4) + "] ���ٳ�һ�ΰ�";
						CQ::sendGroupMsg(group, reply);
					}
					else
						CQ::sendGroupMsg(group, "ҹ�����ɶ������ָ������û���ǩ������");
				}
				break;
				case view:
				{
					if (daily_omikuji_.find(target_qq) != daily_omikuji_.end())
					{
						string reply = "��Ҫ���������ư�����\n" + daily_omikuji_[target_qq];
						CQ::sendGroupMsg(group, reply);
					}
					else
						CQ::sendGroupMsg(group, "ҹ�����ɶ������ָ������û���ǩ������");
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
	}
	return "";
}