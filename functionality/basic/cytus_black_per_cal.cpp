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
		reply = "TP100就没什么必要让我算了吧……";
	else if (IsLegalValue(tp_, Calculate()))
		reply = "计算结果：" + std::to_string(static_cast<int>(black_perfect_)) + "\n可能会不准，如果出错了请原谅……";
	else
		reply = "请你给我一个合法的结算成绩。";
	return reply;
}

void BlackCalculatePrivate::ShowHelpInfo(const int64_t qq, const string msg)
{
	std::regex reg("help\\s算黑[P|p]");
	if (std::regex_match(msg, reg))
		CQ::sendPrivateMsg(qq, help_info_.c_str());
}

void BlackCalculatePrivate::Main(const int64_t qq, const string msg)
{
	std::smatch res;
	std::regex regNM(knm_regex_), regMM(kmm_regex_);
	//重用性太低了，需要改进
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
		reply = at(qq) + "TP100就没什么必要让我算了吧……";
	else if (IsLegalValue(tp_, Calculate()))
		reply = at(qq) + "计算结果：" + std::to_string(static_cast<int>(black_perfect_)) + "\n可能会不准，如果出错了请原谅……";
	else
		reply = at(qq) + "请你给我一个合法的结算成绩。";
	return reply;
}

void BlackCalculateGroup::Main(const int64_t group, const int64_t qq, const string msg)
{
	std::smatch res;
	std::regex regNM(knm_regex_), regMM(kmm_regex_);
	//重用性太低了，需要改进
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
