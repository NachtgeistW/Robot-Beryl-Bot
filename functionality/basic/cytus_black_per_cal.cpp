#include "cytus_black_per_cal.h"

std::string at(int64_t qq) { return "[CQ:at,qq=" + std::to_string(qq) + "] "; }

void ResultInfo::SetResultNum(double tp_int, double tp_frac, double perfect, double good, double bad, double miss)
{
	tp = tp_int + 0.01*tp_frac;
	this->perfect = perfect;
	this->good = good;
	this->bad = bad;
	this->miss = miss;
}

void ResultInfo::SetResultNum(double tp_int, double tp_frac, double perfect)
{
	tp = tp_int + 0.01*tp_frac;
	this->perfect = perfect;
}

void ResultInfo::ShowResult(int64_t group, int64_t qq)
{
	string reply = at(qq) + "计算结果：" + std::to_string(calculation()) + "\n可能会不准，如果出错了请原谅……";
	CQ::sendGroupMsg(group, reply);
}

void ResultInfo::ShowResult(int64_t qq)
{
	string reply = "计算结果：" + std::to_string(calculation()) + "\n可能会不准，如果出错了请原谅……";
	CQ::sendPrivateMsg(qq, reply);
}

void ResultInfo::Main(int64_t group, int64_t qq, string msg)
{
	std::smatch res;
	std::regex regNM(NM);
	std::regex regMM(MM);
	if (std::regex_match(msg, res, regNM))
	{
		SetResultNum(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()),
			std::stod(res[4].str()), std::stod(res[5].str()), std::stod(res[6].str()));
		ShowResult(group, qq);
	}
	else if (std::regex_match(msg, res, regMM))
	{
		SetResultNum(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()));
		ShowResult(group, qq);
	}
	Clear();
}
//需要修改，更简洁一点
void ResultInfo::Main(int64_t qq, string msg)
{
	std::smatch res;
	std::regex regNM(NM);
	std::regex regMM(MM);
	if (std::regex_match(msg, res, regNM))
	{
		SetResultNum(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()),
			std::stod(res[4].str()), std::stod(res[5].str()), std::stod(res[6].str()));
		ShowResult(qq);
	}
	else if (std::regex_match(msg, res, regMM))
	{
		SetResultNum(std::stod(res[1].str()), std::stod(res[2].str()), std::stod(res[3].str()));
		ShowResult(qq);
	}
	Clear();
}