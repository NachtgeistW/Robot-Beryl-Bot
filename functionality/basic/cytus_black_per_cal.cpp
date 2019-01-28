#include "cytus_black_per_cal.h"

std::string at(int64_t qq) { return "[CQ:at,qq=" + std::to_string(qq) + "] "; }

void CytusResult::SetCytusResult(const double tp_int, const double tp_frac, const double perfect, 
	const double good = 0, const double bad = 0, const double miss = 0) noexcept
{
	this->tp_ = tp_int + 0.01*tp_frac;
	this->perfect_ = perfect;
	this->good_ = good;
	this->bad_ = bad;
	this->miss_ = miss;
	this->black_perfect_ = Calculate();
}

string BlackCalculatePrivate::ShowResult(const int64_t qq)
{
	string reply;
	if (tp_ == 100.00)
		reply = "TP100��ûʲô��Ҫ�������˰ɡ���";
	else if (IsLegalValue(tp_, Calculate()))
		reply = "��������" + std::to_string(static_cast<int>(black_perfect_)) + "\n���ܻ᲻׼�������������ԭ�¡���";
	else
		reply = "�������һ���Ϸ��Ľ���ɼ���";
	return reply;
}

void BlackCalculatePrivate::ShowHelpInfo(const int64_t qq, const string msg)
{
	std::regex reg("help\\s���[P|p]");
	if (std::regex_match(msg, reg))
		CQ::sendPrivateMsg(qq, help_info_.c_str());
}

void BlackCalculatePrivate::Main(const int64_t qq, const string msg)
{
	std::smatch res;
	std::regex regNM(knm_regex_), regMM(kmm_regex_);
	//������̫���ˣ���Ҫ�Ľ�
	if (std::regex_match(msg, res, regNM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()),
			std::stod(res[4].str()), std::stod(res[5].str()), std::stod(res[6].str()));
		CQ::sendPrivateMsg(qq, ShowResult(qq).c_str());
	}
	else if (std::regex_match(msg, res, regMM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()));
		CQ::sendPrivateMsg(qq, ShowResult(qq).c_str());
	}
	Initialize();
}

string BlackCalculateGroup::ShowResult(const int64_t group, const int64_t qq)
{
	string reply;
	if (tp_ == 100.00)
		reply = at(qq) + "TP100��ûʲô��Ҫ�������˰ɡ���";
	else if (IsLegalValue(tp_, Calculate()))
		reply = at(qq) + "��������" + std::to_string(static_cast<int>(black_perfect_)) + "\n���ܻ᲻׼�������������ԭ�¡���";
	else
		reply = at(qq) + "�������һ���Ϸ��Ľ���ɼ���";
	return reply;
}

void BlackCalculateGroup::Main(const int64_t group, const int64_t qq, const string msg)
{
	std::smatch res;
	std::regex regNM(knm_regex_), regMM(kmm_regex_);
	//������̫���ˣ���Ҫ�Ľ�
	if (std::regex_match(msg, res, regNM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()),
			std::stod(res[4].str()), std::stod(res[5].str()), std::stod(res[6].str()));
		CQ::sendGroupMsg(group, ShowResult(group, qq).c_str());

	}
	else if (std::regex_match(msg, res, regMM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()));
		CQ::sendGroupMsg(group, ShowResult(group, qq).c_str());
	}
	Initialize();
}
