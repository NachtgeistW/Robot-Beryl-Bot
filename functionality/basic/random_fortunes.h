#pragma once
#include "../../util/util.h"

class Omikuji
{
public:
	Omikuji();
	~Omikuji() = default;

	string ShowHelpInfo(string msg);
	void GetDailyOmikuji(int64_t qq);
	string ShowOmikujiPrivate(int64_t qq, string msg);
	string ShowOmikujiGroup(int64_t qq, string msg);
	void ResetOmikuji(void);
	string MasterCommand(int64_t group, int64_t qq, string msg);

private:
	std::map<int64_t, string> daily_omikuji_;
	time_t origin_t;
	int RandInt_binomial(double expected, double variance, int64_t qq)
	{
		static std::normal_distribution<> dist(expected, variance);//二项式分布生成随机数
		//static std::random_device device;						//随机数引擎，需要mt
		static std::mt19937_64 gen(qq);					//给mt提供种子。第一个抽签的人是谁，就用谁做种子
		return lround(dist(gen));
	}
};