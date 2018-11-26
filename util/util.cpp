#include "util.h"

int util::RandInt_uniform(int begin, int end)
{
	std::uniform_int_distribution<int> dist(begin, end);	//������ֲ�����������begin��end�����
	static std::random_device device;						//��������棬��Ҫmt
	static std::mt19937 gen(device());						//��mt�ṩ����
	return dist(gen);
}

bool util::checkBot(int64_t QQID, std::vector<int64_t>bot)
{
	for (auto begin = bot.begin(); begin != bot.end(); begin++)
		if (*begin == QQID)
			return true;
	return false;
}

std::string util::int64_ttos(int64_t num)
{
	std::string result;
	std::stringstream trans;
	trans << num;
	trans >> result;
	return result;
}