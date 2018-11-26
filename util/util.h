#pragma once
#include <CQAPI_EX.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <regex>
#include <map>

using std::string;
namespace util {
	const int64_t Beryl = 3276553814;		//机器人的QQ号
	const int64_t Master = 562231326;	//主人的QQ号
	const std::string path = "conf\\";

	int RandInt_uniform(int begin, int end);

	static std::vector<int64_t> Robot{ 2718434132, 3304584594, 3461119188, 2748920600, 2130638764,530752474 };
	//bool getBot(std::vector<int64_t>& bot);
	bool checkBot(int64_t QQID, std::vector<int64_t>bot);

	std::string int64_ttos(int64_t num);
}