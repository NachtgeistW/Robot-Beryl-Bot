#include "random_fortunes.h"
#include <cmath>
#include <chrono>

string Omikuji::ShowHelpInfo(string msg)
{
	if (!msg.compare("help Omikuji") || !msg.compare("help ��ǩ"))
	{
		return string ("���ǿ��������µĻ���\n"
			"����ǩ�����Գ�һ���������������ơ�ÿ�������̻�����������ݣ�����ÿ�춼���Գ�һ�Ρ�\n"
			"�﷨Ϊ��@���� ��������/��ǩ��������Ҳ�ǿ��Եġ�\n"
			"���˳̶ȴ���õ������Ϊ�󼪡��м���С��������ĩ�����ס����ס�"
			"�����ž��ǲ���Ҳ������"
			"���ֶ����������У�����Ҳ�ա�����ף��λ�ո���죨Ц����");
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
		Omikuji = "�� / Great Blessing\n��*�b�`�b*����\n�����ʲôҲ�����˿�ȥ�ո�ɣ�";
		break;
	case 1:
		Omikuji = "�м� / Middle Blessing\n�Ҳ��������Ļ���һ�����кý���İ�:-D";
		break;
	case 2:
		Omikuji = "С�� / Small Blessing\n��Ž����������ľ�ϲ��";
		break;
	case 3:
		Omikuji = "�� / Blessing\n����Ҳ������";
		break;
	case 4:
		Omikuji = "ĩ�� / Ending Blessing\n����Ӧ�ò������ո�ĺ�ʱ�䣬�������������(������)\"";
		break;
	case 5:
		Omikuji = "�� / Curse\nǩ��˵���첻�˴��>.<";
		break;
	case 6:
		Omikuji = "����  / Great Curse\n����ȷ����һ���Ǵ��ס���Ҫ�������ȥ����������";
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
	std::regex reg("(��������|�����\��|��ǩ|��`)(\\[CQ:at,qq=)?(" + std::to_string(util::Beryl) + ")?(\\])?(.*)?");
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
			return "���Ѿ�����ǩͲ������µ�ǩ�ˡ�ҹ�ַ��ģ���ҡ�úܾ��ȵģ�";
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
					return string("�ã���������[CQ:at,qq=" + match.str(3) + "] ���ٳ�һ�ΰ�");
				}
				else
					return "ҹ�����ɶ������ָ������û���ǩ������";
			}
		} catch (std::regex_error e) {
			string error = e.what() + e.code();
			CQ::sendPrivateMsg(util::Master, error.c_str());
		}
	}
	return "";
}