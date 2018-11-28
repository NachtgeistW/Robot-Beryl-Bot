#pragma once
#include "../../util/util.h"
class Omikuji
{
public:
	Omikuji() = default;
	~Omikuji() = default;

	string ShowHelpInfo(string msg);
	void GetDailyOmikuji(int64_t qq);
	string ShowOmikujiPrivate(int64_t qq, string msg);
	string ShowOmikujiGroup(int64_t qq, string msg);
	void ResetOmikuji(void);
	string MasterCommand(int64_t qq, string msg);

private:
	std::map<int64_t, string> daily_omikuji_;
	int RandInt_binomial(double expected, double variance)
	{
		static std::normal_distribution<> dist(expected, variance);//����ʽ�ֲ����������
		static std::random_device device;						//��������棬��Ҫmt
		static std::mt19937_64 gen(device());					//��mt�ṩ����
		return lround(dist(gen));
	}
};