#include "cytus_black_per_cal.h"

std::string at(int64_t qq) { return "[CQ:at,qq=" + std::to_string(qq) + "] "; }

void CytusResult::SetCytusResult(const double tp_int, const double tp_frac, const double perfect, const double miss = 0, const double bad = 0, const double good = 0)
{
	this->tp_ = tp_int + 0.01*tp_frac;
	this->perfect_ = perfect;
	this->good_ = good;
	this->bad_ = bad;
	this->miss_ = miss;
	this->black_perfect_ = Calculate();
}
//this function return the match result 
std::pair<bool, int> CytusResult::Match(const string msg)
{
	return std::pair<bool, int>();
}

void BlackCalculatePrivate::ShowResult(const int64_t qq)
{
	string reply = "计算结果：" + std::to_string(black_perfect_) + "\n验算结果：" + std::to_string(IsLegalValue(tp_, black_perfect_));
	CQ::sendPrivateMsg(qq, reply);
}

void BlackCalculatePrivate::Main(const int64_t qq, const string msg)
{
	std::smatch res;
	std::regex regNM(knm_regex_), regMM(kmm_regex_);
	if (std::regex_match(msg, res, regNM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()),
			std::stod(res[6].str()), std::stod(res[5].str()), std::stod(res[4].str()));
		ShowResult(qq);
	}
	else if (std::regex_match(msg, res, regMM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()));
		ShowResult(qq);
	}
	Initialize();
}

void BlackCalculateGroup::ShowResult(const int64_t group, const int64_t qq)
{
	string reply;
	if (tp_ == 100.00)
		reply = "TP100就没什么必要让我算了吧……";
	else
		reply = at(qq) + "计算结果：" + std::to_string(Calculate()) + "\n可能会不准，如果出错了请原谅……";
	CQ::sendGroupMsg(group, reply);
}

void BlackCalculateGroup::Main(const int64_t group, const int64_t qq, const string msg)
{
	std::smatch res;
	std::regex regNM(knm_regex_);
	std::regex regMM(kmm_regex_);
	if (std::regex_match(msg, res, regNM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()),
 std::stod(res[3].str()),
			std::stod(res[6].str()), std::stod(res[5].str()), std::stod(res[4].str()));
		ShowResult(group, qq);
	}
	else if (std::regex_match(msg, res, regMM))
	{
		SetCytusResult(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()));
		ShowResult(group, qq);
	}
	Initialize();
}
