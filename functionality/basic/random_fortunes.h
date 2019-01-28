#pragma once
#include "../../util/util.h"

class Omikuji
{
public:
	Omikuji();
	~Omikuji() = default;

	string ShowHelpInfo(const string msg);
	void GetDailyOmikuji(const int64_t qq);
	string ShowOmikujiPrivate(const int64_t qq, const string msg);
	string ShowOmikujiGroup(const int64_t qq, const string msg);
	void ResetOmikuji(void);
	string MasterCommand(const int64_t group, const int64_t qq, const string msg);

private:
	std::map<int64_t, string> daily_omikuji_;
	time_t origin_t_;
	int RandIntBinomial(double expected, double variance, int64_t qq)
	{
		static std::normal_distribution<> dist(expected, variance);//����ʽ�ֲ����������
		static std::mt19937_64 gen(qq);					//��mt�ṩ���ӡ���һ����ǩ������˭������˭������
		return lround(dist(gen));
	}
};