#include "util.h"

int util::RandInt_uniform(int begin, int end)
{
	std::uniform_int_distribution<int> dist(begin, end);	//随机数分布，均匀生成begin到end间的数
	static std::random_device device;						//随机数引擎，需要mt
	static std::mt19937 gen(device());						//给mt提供种子
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