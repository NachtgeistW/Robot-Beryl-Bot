#pragma once
#include "../../util/util.h"
class Omikuji
{
public:
	Omikuji() = default;
	~Omikuji() = default;

	void GetDailyOmikuji(int64_t qq);
	void ShowDailyOmikuji (int64_t group, int64_t qq, string msg);
	void ResetOmikuji(int64_t qq, string msg);

	int RandInt_binomial(double expected, double variance, int64_t qq)
	{
		static std::normal_distribution<> dist(expected, variance);//二项式分布生成随机数
		static std::mt19937_64 gen(qq);					//给mt提供种子
		return lround(dist(gen));
	}
private:
	std::map<int64_t, string> daily_omikuji_;
	string command = "(\\[CQ:at,qq=)(" + std::to_string(util::Beryl) + ")(\\])(.*)(今日运势|抽签)";
};